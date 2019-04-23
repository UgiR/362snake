//
// Created by Ugnius on 3/28/2019.
//

#include <cstring>
#include <errno.h>
#include <signal.h>
#include <wiringSerial.h>
#include "Display.h"


Display::Display()
: displayRefreshing{false}, controllerListening{false}, controller_fd(-1)
{
    signal(SIGINT, sigintHandler);
    for (int i = 0; i < 16; ++i) {
        this->bitMatrix[i] = 0xFFFF;
        this->bitMatrixStaging[i] = 0xFFFF;
    }

    wiringPiSetup();
    pinMode(P_SER, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(P_SRLCLK, OUTPUT);
    pinMode(P_CLR, OUTPUT);
    pinMode(N_SER, OUTPUT);
    pinMode(N_SRLCLK, OUTPUT);
    pinMode(N_CLR, OUTPUT);

    digitalWrite(P_CLR, HIGH);
    digitalWrite(N_CLR, HIGH);
}

Display::~Display() {
    for (int i = 0; i < 16; ++i) {
        this->bitMatrix[i] = 0xFFFF;
        this->bitMatrixStaging[i] = 0xFFFF;
    }
    displayRefreshing = false;
    controllerListening = false;
    toggle(P_CLR);
    toggle(N_CLR);
}

void Display::shiftOut(uint_fast16_t data, int serial, int clock) {
    for (int i = 0; i < 16; ++i) {
        digitalWrite(serial, (data >> i) & 0b1);
        toggle(clock);
    }
}

void Display::toggle(int pin) {
    int currState = digitalRead(pin);
    digitalWrite(pin, !currState);
    digitalWrite(pin, currState);
}

void Display::refresh() {
    // Set initial y-axes bit to position 0
    digitalWrite(P_SER, 0b1);
    toggle(P_SRLCLK);

    for (int i = 0; i < 16; ++i) {
        // Shift out x-axis pattern
        shiftOut(this->bitMatrix[i], N_SER, N_SRLCLK);
        toggle(RCLK);

        // Advance y-axis bit to next position
        digitalWrite(P_SER, 0b0);
        toggle(P_SRLCLK);
    }
}

void Display::getControllerInput(const std::function<void(char)>& f) {
    if (controller_fd == -1) {
        fprintf(stderr, "Controller device not connected\n");
        return;
    }

    int n;
    char in;
    if (n = serialDataAvail(controller_fd)) {
        for (int i = 0; i < n; ++i) {
            in = serialGetchar(controller_fd);
            f(in);
        }
    }
}
}

void Display::resetStage() {
    for (int i = 0; i < 16; ++i) {
        this->bitMatrixStaging[i] = 0xFFFF;
    }
}

void Display::startDisplay() {
    if (!displayRefreshing) {
        displayRefreshing = true;
        std::thread th(
           [&]{while(displayRefreshing.load()) refresh();}
        );
        th.detach();
    }
}

void Display::startController(const std::function<void(char)& callback) {
    if (controller_fd == -1) {
        if ((controller_fd = serialOpen("/dev/ttyUSB0", 9600)) == -1)
            fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
    }

    if (!controllerListening) {
        controllerListening = true;
        std::thread th{
                [&]{while(controllerListening.load()) getControllerInput(callback);}
        };
        th.detach();
    }
}

Display& Display::get() {
    static Display instance;
    return instance;
}

void Display::setPixel(int x, int y, int state) {
    int i = 0x8000 >> x;
    if (state)
        this->bitMatrixStaging[y] &= ~i;
    else
        this->bitMatrixStaging[y] |= i;
}

void Display::update() {
    memcpy(bitMatrix, bitMatrixStaging, sizeof(bitMatrix));
    resetStage();
}

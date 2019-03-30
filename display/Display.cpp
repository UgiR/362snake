//
// Created by Ugnius on 3/28/2019.
//

#include "Display.h"

Display* Display::instance = nullptr;

Display::Display() {
    for (int i = 0; i < 16; ++i) {
        this->bitMatrix[i] = 0xFF;
    }
    wiringPiSetup();
    pinMode(SER, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(SRLCLK, OUTPUT);
}

void Display::shiftOut(int data, int serial, int clock) {
    for (int i = 0; i < 16; ++i) {
        digitalWrite(serial, (data >> i) & 0b1);
        digitalWrite(clock, HIGH);
        digitalWrite(clock, LOW);
    }
}

void Display::toggle(int pin) {
    digitalWrite(pin, HIGH);
    digitalWrite(pin, LOW);
}

void Display::refresh() {
    // Set initial y-axes bit to position 0
    digitalWrite(P_SER, 0b1);
    toggle(P_SRLCLK);

    for (int i = 0; i < 16; ++i) {
        // Shift out x-axis pattern
        shiftOut(this->bitMatrix[i], N_SER, N_SRLCLK);
        //toggle(RCLK); // TODO: universal rclk
        toggle(P_RCLK);
        toggle(N_RCLK);

        // Advance y-axis bit to next position
        digitalWrite(P_SER, 0b0);
        toggle(P_SRLCLK);
    }
}

void Display::start() {
    std::thread th(
            []{while(true) refresh();}
    );
}

Display& Display::get() {
    static Display instance;
    return instance;
}

void Display::setPixel(int x, int y, int state) {
    int i = 0x8000 >> x;
    if (state)
        this->bitMatrix[y] |= i;
    else
        this->bitMatrix[y] &= ~i;
}
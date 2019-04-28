//
// Created by Ugnius on 4/22/2019.
//

#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <wiringPi.h>
#include <string.h>
#include "display/Display.h"
#include "snake/SSnake.h"

volatile sig_atomic_t interrupted = 0;

void sigintHandler(int sig) {
    interrupted = 1;
}

void init() {
    struct sigaction sigint_sa;
    sigint_sa.sa_handler = sigintHandler;
    sigemptyset(&sigint_sa.sa_mask);
    sigint_sa.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &sigint_sa, NULL) < 0) {
        fprintf(stderr, "sigaction error: %s\n", strerror(errno));
        exit(0);
    }
}

int main() {
    init();

    SSnake s;
    Display& d = Display::get();

    d.startController([&](char in) {
        if (isdigit(in)) {
            int in_ = in - '0';
            s.changeDirection((direction)in_);
        }
    });

    d.startDisplay();

    while (!interrupted && s.getGameRunning()) {
        delay(400);
        s.move();
        s.loadToDisplay(d);
        d.update();
    }

    int score = s.getScore();
    // HTTP REQUEST TODO
}

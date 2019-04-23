//
// Created by Ugnius on 4/22/2019.
//

#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include "display/Display.h"
#include "snake/SSnake.h"

volatile sig_atomic_t interrupted = 0;

void sigintHandler(int sig) {
    interrupted = 1;
}

int main() {
    signal(SIGINT, sigintHandler);

    SSnake s;
    Display& d = Display::get();

    d.startController([&](char in) {
        if (isdigit(in)) {
            int in_ = in - '0';
            s.changeDirection((direction)in_);
        }
    });

    d.startDisplay();

    while (!interrupted) {
        delay(400);
        s.move();
        s.loadToDisplay(d);
        d.update();
    }
}

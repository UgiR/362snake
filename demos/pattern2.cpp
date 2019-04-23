//
// Created by Ugnius on 4/23/2019.
//

#include <unistd.h>
#include <signal.h>
#include "../display/Display.h"

volatile sig_atomic_t interupt = 0;

void sigint_handler(int sig) {
    interupt = 1;
}

int main() {
    signal(SIGINT, sigint_handler);
    Display& d = Display::get();
    d.startDisplay();
    while(true){
        for (int x = 0; x < 16; ++x) {
            d.setPixel(x, x, 1);
            d.setPixel(15-x, 15-x, 1);
            d.setPixel(15-x, x, 1);
            d.setPixel(x, 15-x, 1);
            d.update();
            delay(200);
            d.setPixel(x, x, 0);
            d.setPixel(15-x, 15-x, 0);
            d.setPixel(15-x, x, 0);
            d.setPixel(x, 15-x, 0);
            d.update();
        }
    }
    return 0;
}

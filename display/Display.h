//
// Created by Ugnius on 3/28/2019.
//

#ifndef INC_362SNAKE_DISPLAY_H
#define INC_362SNAKE_DISPLAY_H

#include <wiringPi.h>
#include <thread>
#include <unistd.h>

/**
 * SER    : serial
 * RCLK   : register clock
 * SRLCLK : serial clock
 * CLR    : clear
 *
 * Prefixes:
 * P_ : pin for 'positive' connection
 * N_ : pin for 'negative' connection
 *
 */
#define P_SER 0
#define P_RCLK 1
#define P_SRLCLK 2
#define P_CLR 3

#define N_SER 22
#define N_RCLK 23
#define N_SRLCLK 24
#define N_CLR 25

/**
 * Display driver for Snake Display
 * This is a singleton class, only one instance will be created.
 *
 * Usage:
 *     Display display = Display::get();
 *     display.setPixel(...);
 */
class Display {
private:
    int bitMatrix[16];

    Display();

    void shiftOut(int data, int serial, int clock);

    void toggle(int pin);

    void refresh();

public:
    Display(const Display& display) = delete;
    Display(const Display&& display) = delete;
    Display& operator=(const Display&) = delete;
    Display& operator=(const Display&&) = delete;

    void start();

    static Display& get();

    void setPixel(int x, int y, int state);

};

#endif //INC_362SNAKE_DISPLAY_H

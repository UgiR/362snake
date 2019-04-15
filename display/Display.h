//
// Created by Ugnius on 3/28/2019.
//

#ifndef INC_362SNAKE_DISPLAY_H
#define INC_362SNAKE_DISPLAY_H

#include <wiringPi.h>
#include <thread>
#include <atomic>
#include <unistd.h>
#include <stdint.h>

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
    std::atomic<bool> refreshThreadRunning;

    Display();

    /**
     * Shifts out 16 bits using the given serial and clock pins
     *
     * @param data data to shift out
     * @param serial serial pin number
     * @param clock serial clock pin number
     */
    void shiftOut(uint_fast16_t data, int serial, int clock);

    /**
     * Toggles pin - sets HIGH, then LOW
     * @param pin pin to toggle
     */
    void toggle(int pin);

    /**
     * Refreshes display based on pattern in bitMatrix
     */
    void refresh();

public:
    Display(const Display& display) = delete;
    Display(const Display&& display) = delete;
    Display& operator=(const Display&) = delete;
    Display& operator=(const Display&&) = delete;

    /**
     * Spawns thread to constantly refresh display
     */
    void start();

    /**
     *
     * @return singleton Display instance
     */
    static Display& get();

    /**
     * Sets pixel on (HIGH) or off (LOW)
     * @param x x-coord of pixel
     * @param y y-coord of pixel
     * @param state HIGH/LOW (1/0)
     */
    void setPixel(int x, int y, int state);

};

#endif //INC_362SNAKE_DISPLAY_H

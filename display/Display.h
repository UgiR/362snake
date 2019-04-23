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
 **** Physical Design ****
 * To better understand the code contained in Display.cpp, an explanation of the hardware is provided below
 *
 * NOTE:
 * Two 595 shift registers are daisy-chained to allow for 16 outputs. Because these two 595's behave as a single 16-bit
 * register, it will be referred to as a '16-bit register' throughout this documentation, even though they are
 * technically two separate registers.
 *
 * The physical display is a 16 x 16 matrix of LED's, making up a total of 256 individual LEDs. In every row of the
 * matrix, each LEDs' cathodes are connected in parallel. In every column of the matrix, each LEDs' anodes are connected
 * in parallel. All rows are connected to a 16-bit register and all columns are connected to a different 16-bit register.
 * These registers' pins are differentiated below by a prefix. The register corresponding to the rows (the negative
 * connections) is controlled by the pins prefixed by 'N_'. The register corresponding to the columns (the positive
 * connections) is controlled by the pins prefixed by 'P_'.
 *
 **** Driving the Physical Display ****
 * With the physical design as described above, one would toggle an individual LED by grounding the row the LED resides
 * in and providing voltage to the column the LED resides in. In the intersection of the row and column, the LED is now
 * pare of a complete circuit. This works as intended for simple patterns such as straight lines but cannot produce more
 * complex patterns such as diagonals. Attempting to display a diagonal line with the technique described would result
 * in a square shape being displayed.
 *
 * To allow for more complex shapes, the driver class must not toggle all LED's of the intended pattern simultaneously.
 * Instead, the driver must loop over each row and display each row's pattern sequentially. This happens fast enough
 * for the human eye to interpret the pattern as being displayed concurrently.
 *
 * A side effect of this technique is that it mimics pulse width modulation. This means that the average current
 * received by each LED is lower, resulting in a dimmer light.
 *
 *
 **** PIN DEFINITIONS ****
 *
 * SER    : serial
 * RCLK   : register clock
 * SRLCLK : serial clock
 * CLR    : clear
 *
 * Prefixes:
 * P_ : pin for 'positive' connection
 * N_ : pin for 'negative' connection
 *
 * Both registers share the register clock
 *
 * WiringPi's pin numbering system is used
 * Pin numbers are NOT referencing GPIO pin numbers
 * More info on WiringPi pin numbering:
 * http://wiringpi.com/pins/
 */

#define RCLK 1

#define P_SER 0
#define P_SRLCLK 2
#define P_CLR 3

#define N_SER 22
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
    int bitMatrixStaging[16];
    std::atomic<bool> displayRefreshing;
    std::atomic<bool> controllerListening;
    int controller_fd;

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
     * Toggles pin - Sets pin to inverse of current state, and returns to current state
     * @param pin pin to toggle
     */
    void toggle(int pin);

    /**
     * Refreshes display based on pattern in bitMatrix
     */
    void refresh();

    void getControllerInput(const std::function<void(char)>& f);

    void resetStage();

public:

    Display(const Display& display) = delete;
    Display(const Display&& display) = delete;
    Display& operator=(const Display&) = delete;
    Display& operator=(const Display&&) = delete;

    ~Display();

    /**
     * Spawns thread to constantly refresh display
     */
    void startDisplay();

    void startController(const std::function<void(char)>& callback);

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

    void update();

};

#endif //INC_362SNAKE_DISPLAY_H

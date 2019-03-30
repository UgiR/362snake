//
// Created by Ugnius on 3/28/2019.
//

#ifndef INC_362SNAKE_DISPLAY_H
#define INC_362SNAKE_DISPLAY_H

#include <wiringPi.h>
#include <thread>

#define P_SER 11
#define P_RCLK 12
#define P_SRLCLK 13
#define P_CLR 15

#define N_SER 31
#define N_RCLK 33
#define N_SRLCLK 35
#define N_CLR 37

class Display {
private:
    static Display *instance; //init to nullptr in .c file
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

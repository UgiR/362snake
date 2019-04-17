//
// Created by Ugnius on 4/17/2019.
//

#include <iostream>
#include "uint4.h"

enum direction {
    left = 1,
    right = 2,
    up = 3,
    down = 4
};

class SSnake {
private:

    class Segment {
    public:
        Segment(uint4 x, uint4 y)
        : next(nullptr), prev(nullptr) {
            this->x = x;
            this->y = y;
        }

    //private:
        uint4 x;
        uint4 y;
        Segment *next;
        Segment *prev;

    public:
        Segment *getNext() {
            return next;
        }

        Segment *getPrev() {
            return prev;
        }

        uint4 getX() {
            return x;
        }

        uint4 getY() {
            return y;
        }
    };

    Segment *head;
    Segment *tail;
    direction dir;

    bool debug[16][16];

    void append(Segment *s) {
        s->prev = this->tail;
        this->tail->next = s;
        this->tail = s;
    }

public:

    SSnake() {
        this->head = new Segment(8, 8);
        this->tail = head;
        append(new Segment(8, 9));
        for (int x = 0; x < 16; ++x) {
            for (int y = 0; y < 16; ++y) {
                debug[x][y] = false;
            }
        }
    }

    void grow() {
        Segment *t0;
        Segment *t1;
        t0 = this->tail;
        if (t0) t1 = t0->prev;

        uint4 dx = t0->x - t1->x;
        uint4 dy = t0->y - t1->y;

        Segment *s = new Segment(tail->x + dx, tail->y + dy);
        append(s);
    }

    void move() {
        uint4 dx = 0;
        uint4 dy = 0;

        switch(dir) {
            case left:
                dx = -1;
                break;
            case right:
                dx = 1;
                break;
            case up:
                dy = 1;
                break;
            case down:
                dy = -1;
                break;
        }

        uint4 px = head->x;
        uint4 py = head->y;

        head->x += dx;
        head->y += dy;

        Segment *curr = head->next;
        while(curr) {
            uint4 temp_px = curr->x;
            uint4 temp_py = curr->y;
            curr->x = px;
            curr->y = py;
            px = temp_px;
            py = temp_py;
            curr = curr->next;
        }
    }

    void changeDirection(direction dir) {
        this->dir = dir;
    }

    void printDebug() {
        Segment *s = this->head;
        while(s) {
            debug[(int)s->x][(int)s->y] = true;
            s = s->next;
        }

        for (int x = 0; x < 16; ++x) {
            for (int y = 0; y < 16; ++y) {
                char c;
                if (debug[x][y]) c = 'O';
                else c = '-';
                std::cout << (char)c << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        for (int x = 0; x < 16; ++x) {
            for (int y = 0; y < 16; ++y) {
                debug[x][y] = false;
            }
        }
    }
};

int main() {
    SSnake s;
    s.grow();
    s.grow();
    s.grow();
    s.grow();
    s.printDebug();
    s.changeDirection(left);
    s.move();
    s.printDebug();
    s.move();
    s.printDebug();
    s.move();
    s.printDebug();
    s.move();
    s.printDebug();
    s.move();
    s.printDebug();
    s.move();
    s.printDebug();
    s.move();
    s.printDebug();
    s.move();
    s.printDebug();
    s.move();
    s.printDebug();
}
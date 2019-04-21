//
// Created by Ugnius on 4/17/2019.
//

#include <iostream>
#include <unistd.h>
#include "SSnake.h"
#include "display/Display.h"


SSnake::Segment::Segment(uint4 x, uint4 y)
    : next(nullptr), prev(nullptr), x(x), y(y) {}

void SSnake::append(Segment *s) {
    if (tail) { // if tail exists (list is not empty)
        s->prev = tail;
        tail->next = s;
        tail = s;
    }
    else { // list is empty
        head = tail = s;
    }
}

SSnake::SSnake() {
    append(new Segment(8, 8));
    append(new Segment(8, 9));

    /*** Temporary code for debugging ***/
    for (int x = 0; x < 16; ++x) {
        for (int y = 0; y < 16; ++y) {
            debug[x][y] = false;
        }
    }
    /*** End temporary ***/
}

void SSnake::grow() {
    Segment *t0; // last segment of the snake
    Segment *t1; // second-to-last segment of the snake
    t0 = this->tail;
    t1 = t0->prev;

    // Find the difference between the x and y coordinates between the two segments
    // This is necessary to determine where the new segment will be places, relative to the tail
    uint4 dx = t0->x - t1->x;
    uint4 dy = t0->y - t1->y;

    Segment *s = new Segment(tail->x + dx, tail->y + dy);
    append(s);
}

void SSnake::move() {
    // dx and dy are the changes we must make to the head segment for it to move in the correct direction
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
            dy = -1;
            break;
        case down:
            dy = 1;
            break;
    }

    uint4 px = head->x;
    uint4 py = head->y;

    // Change head segment coordinates in the correct direction
    head->x += dx;
    head->y += dy;

    // Move all following segments forward
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

void SSnake::changeDirection(direction dir) {
    this->dir = dir;
}

void SSnake::printDebug() {
    Segment *s = this->head;
    while(s) {
        debug[(int)s->x][(int)s->y] = true;
        s = s->next;
    }

    for (int x = 0; x < 16; ++x) {
        for (int y = 0; y < 16; ++y) {
            char c;
            if (debug[y][x]) c = 'O';
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
    usleep(500*1000);
    std::cout << "\033[2J\033[1;1H"; // clear screen
}

void SSnake::printDisplay() {
    Display& d = Display::get();
    Segment *s = head;
    while(s) {
        d.setPixel(s->x, s->y);
        s = s->next;
    }
    d.update();
    usleep(500*1000);
}

int main() {
    SSnake s;
}

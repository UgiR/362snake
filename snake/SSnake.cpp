//
// Created by Ugnius on 4/17/2019.
//

#include "SSnake.h"
#include "../display/Display.h"


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

SSnake::SSnake()
: head(nullptr), tail(nullptr), dir{up}
{
    append(new Segment(8, 8));
    append(new Segment(8, 9));
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

    switch(dir.load()) {
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

void SSnake::loadToDisplay(Display& display) {
    Segment *s = head;
    while(s) {
        display.setPixel(s->x, s->y, 1);
        s = s->next;
    }
}

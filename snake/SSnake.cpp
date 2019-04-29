//
// Created by Ugnius on 4/17/2019.
//

#include <stdlib.h>
#include <time.h>
#include "SSnake.h"
#include "../display/Display.h"


SSnake::Segment::Segment(uint4 x, uint4 y)
    : next(nullptr), prev(nullptr), x(x), y(y) {}

SSnake::SSnake()
        : gameRunning(true), head(nullptr), tail(nullptr), dir{up}, food(rand15(), rand15())
{
    append(new Segment(8, 8));
    append(new Segment(8, 9));
}

~SSnake() {
    Segment *s = head;
    Segment *temp;
    while (s) {
        temp = s->next;
        free(s);
        s = temp;
    }
}

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

bool SSnake::withinSnake(int x, int y, bool includeHead = true) {
    Segment *s = head;
    if (!includeHead) s = s->next;
    while(s) {
        if ((int)s->x == x && (int)s->y == y) return true;
        s = s->next;
    }
    return false;
}

int SSnake::rand15() {
    static bool seed = false;
    if (!seed) {
        srand(time(NULL));
        seed = true;
    }
    return (rand() % 16);
}

void SSnake::generateFood() {
    int x = rand15();
    int y = rand15();
    while (withinSnake(x, y)) {
        x = rand15();
        y = rand15();
    }
    food = Segment(rand15(), rand15());
}

bool SSnake::getGameRunning() {
    return gameRunning;
}

int SSnake::getScore() {
    int score = 0;
    Segment *s = head;
    while(s) {
        ++score;
        s = s->next;
    }
    return score;
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

    // Check if snake has encountered food
    if (head->x == food.x && head->y == food.y) {
        grow();
        generateFood();
    }

    // Check if snake has collided with itself
    if (withinSnake(head->x, head->y, false)) {
        gameRunning = false;
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

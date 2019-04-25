//
// Created by Ugnius on 4/18/2019.
//

#ifndef INC_362SNAKE_SSNAKE_H
#define INC_362SNAKE_SSNAKE_H

//
// Created by Ugnius on 4/17/2019.
//

#include <atomic>
#include "../util/uint4.h"
#include "../display/Display.h"

enum direction {
    left = 1,
    right = 2,
    up = 3,
    down = 4
};

/**
 * Doubly linked-list implementation of Snake.
 *
 */
class SSnake {
private:

    /**
     * A segment, or 'node', or the linked list representation of a snake.
     * Contains coordinates (x,y) of its location in the grid
     */
    class Segment {
    public:
        /**
         * Constructor
         * @param x x-coordinate of segment
         * @param y y-coordinate of segment
         */
        Segment(uint4 x, uint4 y);

    private:
        friend class SSnake;
        uint4 x;
        uint4 y;
        Segment *next;
        Segment *prev;
    };


    Segment *head;  // head/front of snake
    Segment *tail;  // tail/end of snake
    Segment food;
    std::atomic<direction> dir;  // direction snake is moving
    bool gameRunning;

    /**
     * Appends a segment to the end of the snake
     * @param s Segment* to append
     */
    void append(Segment *s);

    bool withinSnake(int x, int y);

    static int rand15();

    void generateFood();

public:

    /**
     * Constructor
     * Creates a snake with 2 initial segments
     */
    SSnake();

    bool getGameRunning();

    int getScore();

    /**
     * Grows the snake by adding one segment to the end of the snake
     */
    void grow();

    /**
     * Moves the snake 1 tile based on the direction it is travelling
     * Snake must be at least 2 segments long, otherwise function behaviour is undefined
     */
    void move();

    /**
     * Changes direction of travel of the snake
     * @param dir new direction
     */
    void changeDirection(direction dir);

    void loadToDisplay(Display& display);
};

#endif //INC_362SNAKE_SSNAKE_H

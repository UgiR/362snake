//
// Created by Ugnius on 4/17/2019.
//

#ifndef INC_362SNAKE_UINT4_H
#define INC_362SNAKE_UINT4_H

/**
 * uint4 - 4-bit unsigned integer
 * Operator functionality may be incomplete!!
 *
 * Purpose for snake:
 * A 4-bit integer will simplify the implementation of at least one snake feature.
 *
 * For example, when the snake encounters the end of the grid, it should "wrap around" and continue on the other side
 * of the grid. A 4-bit integer will naturally overflow and will reset to 0, so there will be no need to implement
 * this behaviour manually.
 */
class uint4 {
private:
    unsigned int i : 4;

public:
    uint4();

    uint4(unsigned int x);

    uint4& operator=(const uint4& rx);

    uint4& operator=(const unsigned int& rx);

    uint4& operator+=(const uint4& rx);

    uint4& operator+=(const int& rx);

    friend uint4 operator+(uint4 lx, const uint4& rx);

    friend uint4 operator+(uint4 lx, const int& rx);

    uint4& operator-=(const uint4& rx);

    friend uint4 operator-(uint4 lx, const uint4& rx);

    friend bool operator==(const uint4& lx, const uint4& rx);

    friend bool operator!=(const uint4& lx, const uint4& rx);

    friend bool operator<(const uint4& lx, const uint4& rx);

    friend bool operator>(const uint4& lx, const uint4& rx);

    friend bool operator<=(const uint4& lx, const uint4& rx);

    friend bool operator>=(const uint4& lx, const uint4& rx);

    operator int() const ;
};

#endif //INC_362SNAKE_UINT4_H

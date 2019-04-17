//
// Created by Ugnius on 4/17/2019.
//

#ifndef INC_362SNAKE_UINT4_H
#define INC_362SNAKE_UINT4_H

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

    friend inline bool operator==(const uint4& lx, const uint4& rx);

    friend inline bool operator!=(const uint4& lx, const uint4& rx);

    friend inline bool operator<(const uint4& lx, const uint4& rx);

    friend inline bool operator>(const uint4& lx, const uint4& rx);

    friend inline bool operator<=(const uint4& lx, const uint4& rx);

    friend inline bool operator>=(const uint4& lx, const uint4& rx);

    operator int() const ;
};

#endif //INC_362SNAKE_UINT4_H

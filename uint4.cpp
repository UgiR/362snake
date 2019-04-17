//
// Created by Ugnius on 4/17/2019.
//

/**
 * 4-bit unsigned integer
 */

#include "uint4.h"

uint4::uint4()
: i(0) {}

uint4::uint4(unsigned int x)
: i(x){}

uint4& uint4::operator=(const uint4& rx) {
    this->i = rx.i;
    return *this;
}

uint4& uint4::operator=(const unsigned int& rx) {
    this->i = rx;
    return *this;
}

uint4& uint4::operator+=(const uint4& rx) {
    this->i += rx.i;
    return *this;
}

uint4& uint4::operator+=(const int& rx) {
    this->i += rx;
    return *this;
}

uint4 operator+(uint4 lx, const uint4& rx) {
    lx += rx;
    return lx;
}

uint4 operator+(uint4 lx, const int& rx) {
    lx += rx;
    return lx;
}

uint4& uint4::operator-=(const uint4& rx) {
    this->i -= rx.i;
    return *this;
}

uint4 operator-(uint4 lx, const uint4& rx) {
    lx -= rx;
    return lx;
}

bool operator==(const uint4& lx, const uint4& rx) {
    return (lx.i == rx.i);
}

bool operator!=(const uint4& lx, const uint4& rx) {
    return !operator==(lx, rx);
}

bool operator<(const uint4& lx, const uint4& rx) {
    return (lx.i < rx.i);
}

bool operator>(const uint4& lx, const uint4& rx) {
    return operator<(rx, lx);
}

bool operator<=(const uint4& lx, const uint4& rx) {
    return !operator>(lx, rx);
}

bool operator>=(const uint4& lx, const uint4& rx) {
    return !operator<(lx, rx);
}

uint4::operator int() const {
    return this->i;
}
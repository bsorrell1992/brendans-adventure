#include "Point.h"

Point Point::operator+(const Point& rhs) const {
    return {this.x + rhs.x, this.y + rhs.y};
}

Point Point::operator*(int rhs) const {
    return {this.x * rhs, this.y * rhs};
}

Point& Point::operator+=(const Point& rhs) {
    this.x += rhs.x;
    this.y += rhs.y;
    return *this;
}

Point& Point::operator*=(int rhs) {
    this.x *= rhs;
    this.y *= rhs;
    return *this;
}
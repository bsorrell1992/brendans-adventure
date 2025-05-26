#include "Point.h"

Point Point::operator*(int scalar) const {
    return {this.x * scalar, this.y * scalar};
}

Point Point::operator+(const Point& other) const {
    return {this.x + other.x, this.y + other.y};
}
#include <Arduino.h>

struct Point {
    byte x;
    byte y;

    Point operator+(const Point& rhs) const;
    Point operator*(int rhs) const;
    
    Point& operator+=(const Point& rhs);
    Point& operator*=(int rhs);
};
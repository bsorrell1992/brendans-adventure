struct Point {
    int x;
    int y;

    Point operator*(int scalar) const;
    Point operator+(const Point& other) const;
};
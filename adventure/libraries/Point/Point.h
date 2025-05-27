template <typename T>
struct Point {
    T x;
    T y;

    Point operator+(const Point& rhs) const;
    Point operator*(int rhs) const;
    
    Point& operator+=(const Point& rhs);
    Point& operator*=(int rhs);
};
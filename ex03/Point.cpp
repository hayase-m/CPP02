#include "Point.hpp"

Point::Point(void) : _x(0), _y(0) {}

Point::Point(float x, float y) : _x(x), _y(y) {}

Point::Point(const Point &other) : _x(other._x), _y(other._y) {}

Point &Point::operator=(const Point &other) { return *this; }

Point::~Point(void) {}

Fixed const Point::getX(void) const { return _x; }
Fixed const Point::getY(void) const { return _y; }
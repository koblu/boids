#include "point.hpp"
using namespace Boids;

Point::Point(): x(0), y(0) {}
Point::Point(double _x,double _y): x(_x), y(_y) {}

void Point::operator+= (const Point p) {
    x += p.x;
    y += p.y;
}
void Point::operator*= (const double l) {
    x *= l;
    y *= l;
}
Point Point::operator+ (const Point p) {
    Point rv;
    rv.x = x + p.x;
    rv.y = y + p.y;
    return rv;
}
Point Point::operator* (const double l) {
    Point rv;
    rv.x = x * l;
    rv.y = y * l;
    return rv;
}
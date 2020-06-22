#include "valuepair.hpp"
using namespace Boids;

ValuePair::ValuePair(): x(0), y(0) {}
ValuePair::ValuePair(double _x,double _y): x(_x), y(_y) {}

void ValuePair::operator+= (const ValuePair p) {
    x += p.x;
    y += p.y;
}
void ValuePair::operator-= (const ValuePair p) {
    x -= p.x;
    y -= p.y;
}
void ValuePair::operator*= (const double l) {
    x *= l;
    y *= l;
}
void ValuePair::operator/= (const double l) {
    if (l == 0.0) {
        throw("Bad Param - Cant Divide By Zero");
    }
    x /= l;
    y /= l;
}
ValuePair ValuePair::operator+ (const ValuePair p) {
    ValuePair rv;
    rv.x = x + p.x;
    rv.y = y + p.y;
    return rv;
}
ValuePair ValuePair::operator- (const ValuePair p) {
    ValuePair rv;
    rv.x = x - p.x;
    rv.y = y - p.y;
    return rv;
}
ValuePair ValuePair::operator* (const double l) {
    ValuePair rv;
    rv.x = x * l;
    rv.y = y * l;
    return rv;
}
ValuePair ValuePair::operator/ (const double l) {
    if (l == 0.0) {
        throw("Bad Param - Cant Divide By Zero");
    }
    ValuePair rv;
    rv.x = x / l;
    rv.y = y / l;
    return rv;
}

double ValuePair::GetX() const {
    return x;
}
double ValuePair::GetY() const{
    return y;
}
void ValuePair::SetX(double _x) {
    x = _x;
}
void ValuePair::SetY(double _y) {
    y = _y;
}
void ValuePair::Set(double _x, double _y) {
    x = _x;
    y = _y;
}
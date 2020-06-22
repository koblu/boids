#include "valuepair.hpp"
using namespace Boids;

/*
    Simple constructors
*/
ValuePair::ValuePair(): x(0), y(0) {}
ValuePair::ValuePair(double _x,double _y): x(_x), y(_y) {}

/*
    Equality operators
*/
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

/*!
    For the ValuePair class, division is defined as scalar multiplication of a vector, where the scalar is less than one
*/
void ValuePair::operator/= (const double l) {
    if (l == 0.0) {
        throw("Bad Param - Cant Divide By Zero");
    }
    x /= l;
    y /= l;
}


/* 
    Arthimetic operators
*/
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

/*!
    For the ValuePair class, division is defined as scalar multiplication of a vector, where the scalar is less than one
*/
ValuePair ValuePair::operator/ (const double l) {
    if (l == 0.0) {
        throw("Bad Param - Cant Divide By Zero");
    }
    ValuePair rv;
    rv.x = x / l;
    rv.y = y / l;
    return rv;
}

/* 
    Getters
*/
double ValuePair::GetX() const {
    return x;
}
double ValuePair::GetY() const{
    return y;
}

/*
    Setters
*/
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
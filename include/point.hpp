#pragma once
namespace Boids {
    struct Point
    {
        double x, y;
        Point();
        Point(double x, double y);
        void operator+= (const Point p);
        void operator*= (const double l);
        void operator/= (const double l);
        Point operator+ (const Point p);
        Point operator* (const double l);
        Point operator/ (const double l);
    };
};
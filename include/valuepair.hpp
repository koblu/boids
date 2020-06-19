#pragma once
namespace Boids {
    struct ValuePair
    {
        double x, y;
        ValuePair();
        ValuePair(double x, double y);
        void operator+= (const ValuePair p);
        void operator-= (const ValuePair p);
        void operator*= (const double l);
        void operator/= (const double l);
        ValuePair operator+ (const ValuePair p);
        ValuePair operator- (const ValuePair p);
        ValuePair operator* (const double l);
        ValuePair operator/ (const double l);
    };
};
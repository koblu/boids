#pragma once

/*!
    @class ValuePair
    @brief A parent class inherited by the Position and Direction classes.
*/

namespace Boids {
    class ValuePair
    {
        friend class Position;
        friend class Direction;
        double x, y;
        
        public:
        double GetX() const;
        double GetY() const;
        void SetX(double _x);
        void SetY(double _y);
        void Set(double _x, double _y);
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
/*
    Boid Simulator
    Written by: Kody Bloodworth
*/
#pragma once
#include <vector>
#include "valuepair.hpp"
namespace Boids
{
    struct Position : public ValuePair {
        Position() {};
        Position(double x, double y) : ValuePair(x, y){};
        void BoundsCheck(double x_bound, double y_bound);
        void operator= (const ValuePair vp);
    };

    struct Direction : public ValuePair {
        Direction() {};
        Direction(double x, double y) : ValuePair(x, y){};
        void Normalize();
        void operator= (const ValuePair vp);
    };

    struct Boid
    {
        Boid(class Swarm &s, double x, double y, double dir_x, double speed);
        
        double speed;
        class Swarm &swarm;
        void Update(unsigned int t);
        Position getPosition() const;
        Direction getDirection() const;
        Position pos;
        Direction dir;

        protected:
        void _UpdateDir();
        double _Dist(Boid b);
        std::vector<Boid*> local;
    };

    class Swarm
    {
        friend class Boid;
        protected:
            std::vector<Boid> pop;
            unsigned int pop_size;
            class Arena &arena;
        public:
            Swarm(class Arena &a, unsigned int pop_size, int seed);
            void Run(unsigned int timesteps, bool print);
            void Print();
    };

    class Arena
    {
        friend class Boid;
        friend class Swarm;
        protected:
            double x_bound, y_bound;
            /*TODO: Add Obstacles List*/

        public:
            Arena(double x_bound, double y_bound);
    };
}; // namespace Boids
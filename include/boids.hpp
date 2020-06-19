/*
    Boid Simulator
*/
#pragma once
#include <vector>
#include "point.hpp"
namespace Boids
{
    struct Triangle
    {
        Point points[3];
    };

    struct Obstacle
    {
        double radius;
        Point pos;
    };

    struct Boid
    {
        Boid(class Swarm &s, double x, double y, double dir_x, double speed);
        
        double speed;
        class Swarm &swarm;
        void Update(unsigned int t);
        Point getPosition() const;
        Point pos;
        Point dir;

        protected:
        void _BoundsCheck();
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
            std::vector<Obstacle> obstacles;

        public:
            Arena(double x_bound, double y_bound);
    };
}; // namespace Boids
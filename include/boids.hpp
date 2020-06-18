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
        std::vector<Triangle> rend;
        Point pos;
    };

    struct Boid
    {
        Boid(class Swarm &s, double x, double y, double dir_x, double dir_y, double speed);
        
        Point pos;
        double dir_x, dir_y;
        double speed;
        class Swarm &swarm;
        void Update(unsigned int t);

        protected:
        void _BoundsCheck();
        void _UpdateDir();
    };

    class Swarm
    {
        friend class Boid;
        protected:
            std::vector<Boid> pop;
            unsigned int pop_size;
            class Arena &arena;
        public:
            Swarm(class Arena &a, unsigned int pop_size);
    };

    class Arena
    {
        friend class Boid;
        protected:
            double x_bound, y_bound;
            std::vector<Obstacle> obstacles;

        public:
            Arena(double x_bound, double y_bound);
            void Run();
    };
}; // namespace Boids
/*
    Boid Simulator
    Written by: Kody Bloodworth
*/
#pragma once
#include <vector>
#include <random>
#include "valuepair.hpp"
namespace Boids
{
    /*  @class Position 
        @brief A class that describes a position within a torus-geometry
            (inherits ValuePair)
    */
    class Position : public ValuePair {
        public:
        Position() : ValuePair(0,0) {};
        Position(double x, double y) : ValuePair(x, y){};
        void BoundsCheck(double x_bound, double y_bound);
        void BoundsCheck(const ValuePair& bounds);
        void operator= (const ValuePair vp);
    };

    /*
        @class Direction 
        @brief a class that is meant to describe a direction vector. 
    */
    class Direction : public ValuePair {
        public:
        Direction() : ValuePair(0,0) {};
        Direction(double x, double y) : ValuePair(x, y){};
        void Normalize();
        void operator= (const ValuePair vp);
    };

    /* 
        @class Boid
        @brief The main object of this simulator, a boid moves in a geometric area
    */
    struct Boid
    {
        Boid(class Swarm &s, double x, double y, double speed);
        double speed;
        void Update(unsigned int t);
        const Position& GetPosition() const;
        const Direction& GetDirection() const;
        class Swarm& GetSwarm() const;

        protected:
        Position pos;
        Direction dir;
        class Swarm &swarm;
        std::vector<Boid*> local;
        double _Dist(const Boid& b);
        double _Dist(const Position& p);
        void _UpdateDir();
    };

    /*
        @class Swarm
        @brief Swarms are groups of boids. Boids make decisions based on others Boids in their swarm
    */

    class Swarm
    {
        friend class Boid;
        protected:
            std::vector<Boid> pop;
            unsigned int pop_size;
            double radius;
            class Arena &arena;
            std::default_random_engine gen;
            std::uniform_real_distribution<double> dist;

        public:
            Swarm(class Arena &a, unsigned int pop_size, double radius, int seed);
            const class Arena& GetArena() const;
            double GetRadius() const;
            Direction GenerateRandomDir();
            void Run(unsigned int timesteps, bool print);
            void Print();
    };

    /*
        @class Arena
        @brief An Arena object contains essential information about the navigatable world
    */

    class Arena
    {
        friend class Boid;
        friend class Swarm;
        protected:
            ValuePair bounds;
            /*TODO: Add Obstacles List*/

        public:
            const ValuePair& GetBounds() const;
            Arena(double x_bound, double y_bound);
    };
}; // namespace Boids
/* 
    Boids Simualtor Source
    Author: Kody Bloodworth
*/

#include "boids.hpp"
#include <random>
#include <cmath>
#include <cstdio>
#include <iostream>

/*! @brief Implementation of boids.hpp */

using namespace Boids;
using namespace std;
/*!
    @brief Enforces torus-like geometry
    @param x_bound is the farthest you can go in the x-direction
    @param y_bound is the farthest you can go in the y-direction
*/
void Position::BoundsCheck(double x_bound, double y_bound) {
    if (x > x_bound) x = 0;
    else if (x < 0)  x = x_bound;
    if (y > y_bound) y = 0;
    else if (y < 0)  y = y_bound;
}

void Position::BoundsCheck(const ValuePair& bounds) {
    BoundsCheck(bounds.GetX(), bounds.GetY());
}

void Position::operator= (const ValuePair vp) {
    x = vp.GetX();
    y = vp.GetY();
}

/*!
    @brief Normalizes a Direction vector
*/
void Direction::Normalize() {
    *this /= sqrt(x*x + y*y);
}

void Direction::operator= (const ValuePair vp) {
    x = vp.GetX();
    y = vp.GetY();
}


/*!
    @brief Boid constructor
    @param s is the Swarm object to which the Boid belongs
    @param x is the Boid's x coord
    @param y is the Boid's y coord
    @param dir_x is the x component of the direction
    @param _speed is the speed of the Boid
*/
Boid::Boid(class Swarm &s, double x, double y, double _speed): swarm(s), pos(Position(x,y)), speed(_speed) {
    dir = swarm.GenerateRandomDir();
}

/*!
    @brief Updates a single Boid by a t number of timesteps
    @param t is the number of timesteps travelled in a given position
*/
void Boid::Update(unsigned int t){
    _UpdateDir();
    pos += (dir * speed);
    pos.BoundsCheck(swarm.GetArena().GetBounds());
};

/*!
    @brief Calculates a single Boid's distance to another Boid.
    @param b is the Boid object in question
*/
double Boid::_Dist(const Boid& b) {
    return _Dist(b.GetPosition());
}
/*!
    @brief Calculates the Boid's distance from some arbitrary position
    @param p is the Position in question
*/

double Boid::_Dist(const Position& p) {
    return sqrt(pow(pos.GetX() - p.GetX(), 2) + pow(pos.GetY() - p.GetY(), 2));
}

/*!
    @brief Updates a single Boid based on the separation, alignment, and cohesion principles
*/
void Boid::_UpdateDir() {
    //We're deriving direction here
    Direction avg_sep;
    Direction avg_dir;
    Direction center;
    Direction to_center;
    double avg_sep_dist, avg_dir_diff, avg_cent_dist;
    int i;
    
    for (auto& boid : swarm.pop) {
        if (_Dist(boid) <= swarm.GetRadius()) {
            local.push_back(&boid);
        }
    }
    if (local.size() > 0) {
        //Separation - We'll take into consideration the average of the distance vectors from them to us.
        avg_sep = Direction(0,0);
        for(int i = 0; i < (int) local.size(); i++) {
            avg_sep += (pos - local[i]->GetPosition());
        }
        if (avg_sep.GetX() == 0 && avg_sep.GetY() == 0) {
            avg_sep = Direction(0,0);
        } else {
            avg_sep /= (int) local.size();
            avg_sep.Normalize();
        }


        //Alignment - We want to align to the local average
        for(int i = 0; i < (int) local.size(); i++) {
            avg_dir += local[i]->dir;
        }
        avg_dir /= (int) local.size();
        avg_dir.Normalize();
        
        //Cohesion - We want to align towards the center of our flock
        for(int i = 0; i < (int) local.size(); i++) {
            center += local[i]->pos;
        }
        center += pos;
        center /= (int) local.size();
        to_center = center - pos;
        to_center.Normalize();

        //Added randomness to simulate movement noise
        dir += (avg_sep + avg_dir + to_center + (swarm.GenerateRandomDir() * 0.05));
        dir.Normalize();
    }
}

/*!
    @brief Position Accessor
*/
inline const Position& Boid::GetPosition() const {
    return pos;
}

/*!
    @brief Direction Accessor
*/
inline const Direction& Boid::GetDirection() const {
    return dir;
}



/*! 
    @brief Swarm constructor
    @param a is the Arena object within which the Swarm "resides"
    @param _pop_size is the size of the population
    @param seed is the seed to a random generator
*/
Swarm::Swarm(class Arena &a, unsigned int _pop_size, double _radius, int seed): arena(a), pop_size(_pop_size), radius(abs(_radius)) {
    int i;
    uniform_real_distribution<double> x_dist(0, a.GetBounds().GetX());
    uniform_real_distribution<double> y_dist(0, a.GetBounds().GetY());
    dist = uniform_real_distribution<double>(-1, 1);

    gen.seed(seed);
    for(i = 0; i < pop_size; i++) {
        pop.push_back(Boid(*this, x_dist(gen), y_dist(gen), 1));
    }
}

/*!
    @brief Runs the Swarm for a given number of timesteps
    @param timesteps is the number of timesteps to be taken in a run
    @param print specifies whether or not to print the Boid's current states after each run.
*/
void Swarm::Run(unsigned int timesteps, bool print) {
    int i;
    for(i = 0; i < timesteps; i++) {
        if (print) Print();
        for (auto& a : pop) {
            a.Update(1);
        }
        //printf("%d\n", i);
    }
}

/*!
    @brief Prints the positions of all Boid objects in the Swarm in a JSON-decodable format
*/
void Swarm::Print() {
    int i;
    Position tmp;
    printf("[");
    for (i = 0; i < pop_size; i++) {
        tmp = pop[i].GetPosition();
        printf("[%.2f, %.2f]", tmp.GetX(), tmp.GetY());
        if (i != pop_size -1) printf(",");
    }
    printf("]\n");
}

/*!
    @brief Generates a random direction vector
*/

Direction Swarm::GenerateRandomDir() {
    Direction d = Direction(dist(gen), dist(gen));
    d.Normalize();
    return d;
}

/*! 
    @brief Arena Accessor
*/
const Arena& Swarm::GetArena() const {
    return arena;
}

/*!
    @brief Swarm Radius Accessor - used by Boids in the Swarm to define "local" Boids
*/
double Swarm::GetRadius() const {
    return radius;
}

/*!
    @brief Arena constructor
    @param _x_bound is the farthest an object can go in the x-direction
    @param _y_bound is the farthest an object can go in the y-direction
*/
Arena::Arena(double x_bound, double y_bound): bounds(x_bound, y_bound) {}

const ValuePair& Arena::GetBounds() const {
    return bounds;
}

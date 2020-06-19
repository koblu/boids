#include "boids.hpp"
#include <random>
#include <cmath>
#include <cstdio>
#include <iostream>

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

/*!
    @brief Normalizes a Direction vector
*/
void Direction::Normalize() {
    *this /= sqrt(x*x + y*y);
}

/*!
    @brief Updates a single Boid by a t number of timesteps
    @param t is the number of timesteps travelled in a given position
*/
void Boid::Update(unsigned int t){
    _UpdateDir();
    pos += (dir * speed);
    pos.BoundsCheck(swarm.arena.x_bound, swarm.arena.y_bound);
};

/*!
    @brief Calculates a single Boid's distance to another Boid.
    @param b is another Boid object
*/
double Boid::_Dist(Boid b) {
    return sqrt(pow(pos.x-b.pos.x,2)+pow(pos.y-b.pos.y,2));
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
    int i;
    
    for (auto& boid : swarm.pop) {
        if (_Dist(boid) < 10.0) {
            local.push_back(&boid);
        }
    }
    if (local.size() > 0) {

        //Separation - We'll take into consideration the average of the distance vectors from them to us.
        avg_sep = Direction(0,0);
        for(int i = 0; i < (int) local.size(); i++) {
            avg_sep += (pos + (local[i]->getPosition() * -1));
        }
        if (avg_sep.x == 0 && avg_sep.y == 0) {
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

        dir += (avg_sep + avg_dir + to_center);
        //std::cout << avg_sep.x << ":" << avg_sep.y << std::endl;
        dir /= sqrt((pow(dir.x,2) + pow(dir.y,2)));
    }
}

/*!
    @brief Position Accessor
*/
inline Position Boid::getPosition() const {
    return pos;
}

/*!
    @brief Direction Accessor
*/
inline Direction Boid::getDirection() const {
    return dir;
}

/*!
    @brief Boid constructor
    @param s is the Swarm object to which the Boid belongs
    @param x is the Boid's x coord
    @param y is the Boid's y coord
    @param dir_x is the x component of the direction
    @param _speed is the speed of the Boid
*/
Boid::Boid(class Swarm &s, double x, double y, double dir_x, double _speed): swarm(s), pos(Position(x,y)), speed(_speed) {
    dir = Direction(dir_x, sqrt(1-pow(dir_x, 2)));
}

/*! 
    @brief Swarm constructor
    @param a is the Arena object within which the Swarm "resides"
    @param _pop_size is the size of the population
    @param seed is the seed to a random generator
*/
Swarm::Swarm(class Arena &a, unsigned int _pop_size, int seed): arena(a), pop_size(_pop_size) {
    int i;
    default_random_engine gen;
    uniform_real_distribution<double> x_dist(0, a.x_bound);
    uniform_real_distribution<double> y_dist(0, a.y_bound);
    uniform_real_distribution<double> dir_dist(0, 1);

    gen.seed(seed);
    for(i = 0; i < pop_size; i++) {
        pop.push_back(Boid(*this, x_dist(gen), y_dist(gen), dir_dist(gen), 1));
    }
}

/*!
    @brief Runs the Swarm for a given number of timesteps
    @params timesteps is the number of timesteps to be taken in a run
    @param print specifies whether or not to print the Boid's current states after each run.
*/
void Swarm::Run(unsigned int timesteps, bool print) {
    int i;
    for(i = 0; i < timesteps; i++) {
        if (print) Print();
        for (auto& a : pop) {
            a.Update(1);
        }
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
        tmp = pop[i].getPosition();
        printf("[%.2f, %.2f]", tmp.x, tmp.y);
        if (i != pop_size -1) printf(",");
    }
    printf("]\n");
}

/*!
    @brief Arena constructor
    @param _x_bound is the farthest an object can go in the x-direction
    @param _y_bound is the farthest an object can go in the y-direction
*/
Arena::Arena(double _x_bound, double _y_bound): x_bound(_x_bound), y_bound(_y_bound) {}

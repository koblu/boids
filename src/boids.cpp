#include "boids.hpp"
#include "point.hpp"
#include <random>
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace Boids;
using namespace std;

void Boid::Update(unsigned int t){
    _UpdateDir();
    pos += (dir * speed);
    _BoundsCheck();
};


void Boid::_BoundsCheck() {
    if (pos.x > swarm.arena.x_bound) pos.x = 0;
    else if (pos.x < 0) pos.x = swarm.arena.x_bound;
    if (pos.y > swarm.arena.y_bound) pos.y = 0;
    else if (pos.y < 0) pos.y = swarm.arena.y_bound;
}

double Boid::_Dist(Boid b) {
    return sqrt(pow(pos.x-b.pos.x,2)+pow(pos.y-b.pos.y,2));
}

void Boid::_UpdateDir() {
    Point avg_sep;
    Point avg_dir;
    Point center;
    Point to_center;
    int i;
    
    for (auto& boid : swarm.pop) {
        if (_Dist(boid) < 10.0) {
            local.push_back(&boid);
        }
    }
    if (local.size() > 0) {

        //Separation - We'll take into consideration the average of the distance vectors from them to us.
        avg_sep = Point(0,0);
        for(int i = 0; i < (int) local.size(); i++) {
            avg_sep += (pos + (local[i]->getPosition() * -1));
        }
        if (avg_sep.x == 0 && avg_sep.y == 0) {
            avg_sep = Point(0,0);
        } else {
            avg_sep /= (int) local.size();
            avg_sep /= sqrt((pow(avg_sep.x,2) + pow(avg_sep.y,2)));
        }


        //Alignment - We want to align to the local average
        for(int i = 0; i < (int) local.size(); i++) {
            avg_dir += local[i]->dir;
        }
        avg_dir /= (int) local.size();
        
        //Cohesion - We want to align towards the center of our flock
        for(int i = 0; i < (int) local.size(); i++) {
            center += local[i]->pos;
        }
        center += pos;
        center /= (int) local.size();
        to_center = center + (pos * -1);

        dir += (avg_sep + avg_dir + to_center);
        //std::cout << avg_sep.x << ":" << avg_sep.y << std::endl;
        dir /= sqrt((pow(dir.x,2) + pow(dir.y,2)));
    }
}

inline Point Boid::getPosition() const{
    return pos;
}

Boid::Boid(class Swarm &s, double x, double y, double dir_x, double _speed): swarm(s), pos(Point(x,y)), speed(_speed) {
    dir = Point(dir_x, sqrt(1-pow(dir_x, 2)));
}


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
void Swarm::Run(unsigned int timesteps, bool print) {
    int i;
    for(i = 0; i < timesteps; i++) {
        if (print) Print();
        for (auto& a : pop) {
            a.Update(1);
        }
    }
}

void Swarm::Print() {
    int i;
    Point tmp;
    printf("[");
    for (i = 0; i < pop_size; i++) {
        tmp = pop[i].getPosition();
        printf("[%.2f, %.2f]", tmp.x, tmp.y);
        if (i != pop_size -1) printf(",");
    }
    printf("]\n");
}

Arena::Arena(double _x_bound, double _y_bound): x_bound(_x_bound), y_bound(_y_bound) {}

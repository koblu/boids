#include "boids.hpp"
#include "point.hpp"

using namespace Boids;
using namespace std;

void Boid::Update(unsigned int t){
    _UpdateDir();
    pos += (Point(dir_x, dir_y) * speed);
    _BoundsCheck();
};

void Boid::_BoundsCheck() {
    if (pos.x >= swarm.arena.x_bound) pos.x = 0;
    else if (pos.x <= 0) pos.x = swarm.arena.x_bound;
    if (pos.y >= swarm.arena.y_bound) pos.y = 0;
    else if (pos.y <= 0) pos.y = swarm.arena.y_bound;
}

void Boid::_UpdateDir() {
    //Separation, Alignment, Cohesion
}

Boid::Boid(class Swarm &s, double x, double y, double _dir_x, double _dir_y, double _speed): swarm(s), pos(Point(x,y)), dir_x(_dir_x), dir_y(_dir_y), speed(_speed){}

Swarm::Swarm(class Arena &a, unsigned int _pop_size): arena(a), pop_size(_pop_size) {}

Arena::Arena(double _x_bound, double _y_bound): x_bound(_x_bound), y_bound(_y_bound) {}
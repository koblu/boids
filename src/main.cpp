#include "boids.hpp"
#include <iostream>

using namespace Boids;
int main() {
    Arena a(0,0);
    Swarm s(a, 1);
    Boid b(s,0,0,1,0,1);
    std::cout << b.pos.x << b.pos.y;
    b.Update(1);
    std::cout << b.pos.x << b.pos.y;
}
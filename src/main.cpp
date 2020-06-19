#include "boids.hpp"
#include <iostream>

using namespace Boids;
int main() {
    Arena a(100,100);
    Swarm s(a, 100, 0);
    s.Run(5000, true);
}
#include "boids.hpp"
#include <iostream>

using namespace Boids;
int main() {
    Arena a(100,100);
    Swarm s(a, 100, 0);
    //std::cout << "Before:\n";
    s.Run(500, true);
    //std::cout << "\nAfter:\n";
}
/*
    main.cpp
    Constructs and runs a Boid simulator
    
    Kody Bloodworth
    June 22 2020
*/

#include "boids.hpp"
#include <iostream>
#include <string>

using namespace Boids;

void quit_with_error(std::string err);

int main(int argc, char** argv) {
    double  width, 
            height,
            radius;
    int     pop_size,
            timesteps;
    unsigned long long seed;
    std::string err;

    if (argc != 7) {
        quit_with_error("Too few arguments");
    }
    width       = std::stod(argv[1]);
    height      = std::stod(argv[2]);
    pop_size    = std::stoi(argv[3]);
    radius      = std::stod(argv[4]);
    seed        = std::stoll(argv[5]);
    timesteps   = std::stoi(argv[6]);

    err = "";
    if ( width <= 0 ) {
        err = "Width too small";
    } else if (height <= 0) {
        err = "Height too small";
    } else if (pop_size < 0) {
        err = "Negative population size";
    } else if (timesteps < 0) {
        err = "Negative timesteps";
    }
    if (err != "") quit_with_error(err);

    Arena a(width, height);
    Swarm s(a, pop_size, radius, seed);
    s.Run(timesteps, true);
}

void quit_with_error(std::string err) {
    std::cerr << "Usage: ./boids [width] [height] [population size] [local radius] [seed] [timesteps]\n";
    std::cerr << err << std::endl;
    exit(1);
}
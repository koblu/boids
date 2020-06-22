# boids
A code sample for a simple "boids" simulator.

As a code sample, it show cases:
1. OOP Design (Inheritance, Polymorphism, etc.)
2. Documentation
3. A basic, Makefile-based build system
4. Familiarity with Unix-based systems

## Background

Boids are a simple example of emergent phenomenon. They were developed by Craig Reynolds in 1986 to simulate the flocking behavior of birds. The classical boid follows three rules:  
1. Try not hit the other boids (Separation)
2. Try to match other boids direction (Alignment)
3. Try to stay with the flock (Cohesion)  

From these few rules, you get emergent flocking phenomenon.

## Compilation
run `make all` to create the executable `bin/boids`  
run `make clean` to clean out these exectables

## Usage
`bin/boids` takes six parameters:

| parameter       | description                                   |
|-----------------|-----------------------------------------------|
| width           | the width of the space                        |
| height          | the height of the space                       |
| population size | the number of boids to generate               |
| local radius    | the radius that boids will consider "local"   |
| seed            | a seed for a random number generator          |
| timesteps       | the number of time steps to run the simulator |

example:
```
UNIX> ./bin/boids  

Usage: ./boids [width] [height] [population size] [local radius] [seed] [timesteps]
Too few arguments  

UNIX> ./bin/boids 100 100 100 5 0 300
```

The `bin/boids` executable generates a series of one-line, JSON-parseable arrays describing the positions of each Boid within the Arena space. 

## Visualizer
Boid behavior is best seen on a large scale - not through numbers. There exists a very basic visualization tool built with the LöVE2D graphics framework. LöVE2D can be installed [here](https://love2d.org/).

To run this viz tool, simply take pipe the output of `bin/boids` to the viz tool.

example:
```
./bin/boids 100 100 100 5 0 300 | love ./love  
```

## Current Issues

As this is a code sample, there are smaller details that have not been touched. As it stands currently, Boids determine direction based on a simple average of the three properties described above. This can cause issues like a Boid "deciding" to hit another Boid because it would rather face the center point. For large population sizes and large radius sizes, the efficiency of this program drops drastically. However, as this is a code sample, these issues are not drastic. If you find any other major issues, I invite you to bring them to my attention.





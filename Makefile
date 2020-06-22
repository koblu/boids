INCLUDE = include
BIN = bin
SRC = src
FLAGS = -O3 -std=c++11 -I$(INCLUDE)

all: $(BIN)/boids


$(BIN)/boids: $(SRC)/main.cpp $(SRC)/boids.cpp $(SRC)/valuepair.cpp bin
	g++ $(FLAGS) -o $(BIN)/boids $(SRC)/main.cpp $(SRC)/boids.cpp $(SRC)/valuepair.cpp

bin:
	mkdir bin

clean:
	rm -rf bin 

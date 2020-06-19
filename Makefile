INCLUDE = include
BIN = bin
SRC = src
FLAGS = -std=c++11 -I$(INCLUDE)

all: $(BIN)/boids


$(BIN)/boids: $(SRC)/main.cpp $(SRC)/boids.cpp $(SRC)/valuepair.cpp
	g++ $(FLAGS) -o $(BIN)/boids $(SRC)/main.cpp $(SRC)/boids.cpp $(SRC)/valuepair.cpp

clean:
	rm -rf bin/* 
#include "asteroid.h"
#include <cmath>
using namespace std;

// Default Constructor
// @param: none
Asteroid::Asteroid() {
	x_position = rand() % 100;
	y_position = rand() % 100;
	size = DEFAULT_SIZE;
	collected = false;
}

// Copy Constructor
// @param: Asteroid to be copied from
Asteroid::Asteroid(Asteroid &other) {
	x_position = other.x_position;
	y_position = other.y_position;
	size = other.size;
	collected = other.collected;
}

// Parameterized Constructor with user defined size
// @param: float to set size
Asteroid::Asteroid(float size) {
	x_position = rand() % 100;
	y_position = rand() % 100;
	this->size = size;
	collected = false;
}

// Parameterized Constructor with user defined coordinates
// @param: 2 ints to set x and y coordinates
Asteroid::Asteroid(int x, int y) {
	x_position = x;
	y_position = y;
	size = DEFAULT_SIZE;
	collected = false;
}

// Parameterized Constructor with user defined coordinates and size
// @param: 2 ints to set x and y coordinates, float to set size
Asteroid::Asteroid(int x, int y, float size) {
	x_position = x;
	y_position = y;
	this->size = size;
	collected = false;
}

// Destructor
Asteroid::~Asteroid() {

}

// Mutator, sets an asteroid with user defined coordinates and size
// @param: 2 ints to set x and y coordinates, float to set size
void Asteroid::set(int x, int y, float size) {
	x_position = x;
	y_position = y;
	this->size = size;
}

// Mutator, sets a flag on when an asteroid has been collected
// @param: none
void Asteroid::collect() { collected = true; }

// Accessor, gets x-coordinate of an asteroid
// @param: none
// @return: int
int Asteroid::getX() const { return x_position; }

// Accessor, gets y-coordinate of an asteroid
// @param: none
// @return: int
int Asteroid::getY() const { return y_position; }

// Accessor, gets size of an asteroid
// @param: none
// @return: float
float Asteroid::getSize() const { return size; }

// Accessor, allows an asteroid to know if it has been collected
// @param: none
// @return: bool
bool Asteroid::isCollected() const { return collected; }

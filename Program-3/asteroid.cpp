#include "asteroid.h"
#include <cmath>
using namespace std;

// Default Constructor
// @param: none
Asteroid::Asteroid() {
	x_position = rand() % 100;
	y_position = rand() % 100;
	size = DEFAULT_SIZE;
	visited = false;
	precious = false;
}

// Copy Constructor
// @param: Asteroid to be copied from
Asteroid::Asteroid(const Asteroid &other) {
	x_position = other.x_position;
	y_position = other.y_position;
	size = other.size;
	visited = other.visited;
	precious = other.precious;
}

// Parameterized Constructor with user defined size
// @param: float to set size
Asteroid::Asteroid(float size) {
	x_position = rand() % 100;
	y_position = rand() % 100;
	this->size = size;
	visited = false;
	precious = false;
}

// Parameterized Constructor with user defined coordinates
// @param: 2 ints to set x and y coordinates
Asteroid::Asteroid(int x, int y) {
	x_position = x;
	y_position = y;
	size = DEFAULT_SIZE;
	visited = false;
	precious = false;
}

// Parameterized Constructor with user defined coordinates and size
// @param: 2 ints to set x and y coordinates, float to set size
Asteroid::Asteroid(int x, int y, float size) {
	x_position = x;
	y_position = y;
	this->size = size;
	visited = false;
	precious = false;
}

// Destructor
Asteroid::~Asteroid() {

}

// Mutator, copies an asteroid
// @precond: an asteroid already exists
// @postcond: all the parameters of the asteroid is copied
// @param: Asteroid to be copied from
void Asteroid::copy(const Asteroid &other) {
	x_position = other.x_position;
	y_position = other.y_position;
	size = other.size;
	visited = other.visited;
	precious = other.precious;
}


// Mutator, sets an asteroid with user defined coordinates, size and metal
// @precond: an asteroid already exists
// @postcond: all the parameters of the asteroid is set to valid values
// @param: 2 ints to set x and y coordinates, float to set size,
//         char to determine whether the metal is precious or not
void Asteroid::set(int x, int y, float size, char metal) {
	setCoordinates(x, y);
	this->size = validate(size);
	if (metal == 'P') { precious = true; }
	else { precious = false; }
}

// Mutator, sets a flag on when an asteroid has been visited by a spacecraft
// @precond: an asteroid has not been visited yet
// @postcond: an asteroid doesn't have to be visited anymore
// @param: none
void Asteroid::visit() { visited = true; }

// Accessor, gets size of an asteroid
// @param: none
// @return: float
float Asteroid::getSize() const { return size; }

// Accessor, allows an asteroid to know if it has been visited by a spacecraft
// @param: none
// @return: bool
bool Asteroid::isVisited() const { return visited; }

// Accessor, tells spacecraft whether an asteroid contains precious metal
// @param: none
// @return: bool
bool Asteroid::isPrecious() const { return precious; }

// Prevents user defined size to be negative
// @param: float
// @return: float
float Asteroid::validate(float size) {
	if (size < 0) { size = size * -1; }
	return size;
}

#include "spaceobject.h"
#include <iomanip>
#include <sstream>
#include <cmath>
using namespace std;

// Default Constructor
// @param: none
SpaceObject::SpaceObject() {
	setCoordinates(rand() % 100, rand() % 100);
	name = "Space Object";
}

// Copy Constructor
// @param: Asteroid to be copied from
SpaceObject::SpaceObject(const SpaceObject &other) {
	setCoordinates(other.x, other.y);
	name = other.name;
}

// Parameterized Constructor with user defined coordinates
// @param: 2 ints to set x and y coordinates
SpaceObject::SpaceObject(int x, int y) {
	setCoordinates(x, y);
	name = "Space Object";
}

// Destructor
SpaceObject::~SpaceObject() {}

// Mutator, sets a space object with user defined coordinates
// @precond: the dimension of the space is set as 100
// @postcond: x and y are in between 0 and 100
// @param: 2 ints to set x and y coordinates
void SpaceObject::setCoordinates(int x, int y) {
	this->x = validate(x);
	this->y = validate(y);
}

// Accessor, gets both coordinates of a space object
// @param: 2 ints, x and y coordinates
// @return: void (pass by reference)
void SpaceObject::getCoordinates(int &x, int &y) {
	x = this->x;
	y = this->y;
}

// Accessor, gets x-coordinate of a space object
// @param: none
// @return: int
int SpaceObject::getX() const { return x; }

// Accessor, gets y-coordinate of a space object
// @param: none
// @return: int
int SpaceObject::getY() const { return y; }

// Accessor, gets a name of space object
// @param: none
// @return: string
string SpaceObject::getName() const { return name; }

// Accessor, tells formatted space object data by string
string SpaceObject::toString() const {
	stringstream stream("");
	stream << "("
		<< setw(3) << right << x << ", "
		<< setw(3) << right << y << ")";
	return stream.str();
}

// Prevents user defined coordinates to be outside of the region
// Such that both x and y must be between 0 and 100
// @param: int, which can be either x or y
// @return: int
int SpaceObject::validate(int z) {
	if (z < 0) { z = 0; }
	else if (z > DIMENSION) { z = DIMENSION; }
	return z;
}

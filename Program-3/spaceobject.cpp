#include "spaceobject.h"
#include <cmath>
using namespace std;

/* Since SpaceObject class is an abstract class, its instance should never be made.
Constructors and destructor are unnecessary.

// Default Constructor
// @param: none
SpaceObject::SpaceObject() {
	x_position = rand() % 100;
	y_position = rand() % 100;
}

// Copy Constructor
// @param: Asteroid to be copied from
SpaceObject::SpaceObject(const SpaceObject &other) {
	x_position = other.x_position;
	y_position = other.y_position;
}

// Parameterized Constructor with user defined coordinates
// @param: 2 ints to set x and y coordinates
SpaceObject::SpaceObject(int x, int y) {
	x_position = x;
	y_position = y;
}

// Destructor
SpaceObject::~SpaceObject() {

}

*/

// Mutator, sets a space object with user defined coordinates
// @precond: the dimension of the space is set as 100
// @postcond: x and y are in between 0 and 100
// @param: 2 ints to set x and y coordinates
void SpaceObject::setCoordinates(int x, int y) {
	x_position = validate(x);
	y_position = validate(y);
}

// Accessor, gets both coordinates of a space object
// @param: 2 ints, x and y coordinates
// @return: void (pass by reference)
void SpaceObject::getCoordinates(int &x, int &y) {
	x = x_position;
	y = y_position;
}

// Accessor, gets x-coordinate of a space object
// @param: none
// @return: int
int SpaceObject::getX() const { return x_position; }

// Accessor, gets y-coordinate of a space object
// @param: none
// @return: int
int SpaceObject::getY() const { return y_position; }

// Prevents user defined coordinates to be outside of the region
// Such that both x and y must be between 0 and 100
// @param: int, which can be either x or y
// @return: int
int SpaceObject::validate(int z) {
	if (z < 0) { z = 0; }
	else if (z > 100) { z = 100; }
	return z;
}

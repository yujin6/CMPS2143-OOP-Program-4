#include "asteroid.h"
#include <iomanip>
#include <sstream>
using namespace std;

// Default Constructor
// @param: none
Asteroid::Asteroid() : SpaceObject() {
	name = "Asteroid";
	size = DEFAULT_SIZE;
	visited = false;
	precious = randomize();
}

// Copy Constructor
// @param: Asteroid to be copied from
Asteroid::Asteroid(const Asteroid &other) : SpaceObject(other) {
	operator=(other);
}

// Parameterized Constructor with user defined size
// @param: float to set size
Asteroid::Asteroid(float size) : SpaceObject() {
	name = "Asteroid";
	this->size = size;
	visited = false;
	precious = randomize();
}

// Parameterized Constructor with user defined coordinates
// @param: 2 ints to set x and y coordinates
Asteroid::Asteroid(int x, int y) : SpaceObject(x, y) {
	name = "Asteroid";
	size = DEFAULT_SIZE;
	visited = false;
	precious = randomize();
}

// Parameterized Constructor with user defined coordinates and size
// @param: 2 ints to set x and y coordinates, float to set size
Asteroid::Asteroid(int x, int y, float size) : SpaceObject(x, y) {
	name = "Asteroid";
	this->size = size;
	visited = false;
	precious = randomize();
}

// Parameterized Constructor with user defined coordinates and size and metal
// @param: 2 ints to set x and y coordinates, float to set size, char to set metal
Asteroid::Asteroid(int x, int y, float size, char metal) : SpaceObject(x, y) {
	name = "Asteroid";
	set(x, y, size, metal);
	visited = false;
}

// Destructor
Asteroid::~Asteroid() {}

// Overload Operator =, copies an Asteroid by deep copy
// @precond: an asteroid already exists
// @postcond: all the parameters of the asteroid is copied
// @param: Asteroid to be copied from
void Asteroid::operator =(const Asteroid &other) {
	name = other.name;
	setCoordinates(other.x, other.y);
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
	(metal == 'P') ? precious = true : precious = false;
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

// Accessor, tells formatted asteroid data by string
// @param: none
// @return: string
string Asteroid::toString() const {
	stringstream stream("");
	string metal, visit;
	(precious) ? metal = "Precious" : metal = "Common";
	(visited) ? visit = "Visited" : visit = "Not Visited";

	stream << "| " << SpaceObject::toString();
	stream << " | "	<< setw(4) << right << fixed << setprecision(1) << size;
	stream << " | " << setw(10) << left << metal;
	stream << " | " << setw(10) << left << visit;
	stream << " |";
	return stream.str();
}

// Prevents user defined size to be negative, for set purpose
// @param: float
// @return: float
float Asteroid::validate(float size) {
	if (size < 0) { size = size * -1; }
	return size;
}

// Allocates precious metal randomly, for constructor purpose
// @param: none
// @return: bool
bool Asteroid::randomize() {
	double fraction = ((double)rand() / (RAND_MAX));
	if (fraction > 0.5) { return true; }
	else { return false; }
}

#include "spaceprobe.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

// Default Constructor
// @param: none
SpaceProbe::SpaceProbe() : Spacecraft() {}

// Copy Constructor
// @param: Spaceship to be copied from
SpaceProbe::SpaceProbe(const SpaceProbe &other) : Spacecraft(other) {}

// Parameterized Constructor with user defined name
// @param: string, to set name
SpaceProbe::SpaceProbe(string n) : Spacecraft(n) {}

// Parameterized Constructor with user defined coordinates
// @param: 2 ints, to set x and y coordinates
SpaceProbe::SpaceProbe(int x, int y) : Spacecraft(x, y) {}

// Parameterized Constructor with user defined name and coordinates
// @param: string and 2 ints, to set name and x and y coordinates
SpaceProbe::SpaceProbe(string n, int x, int y) : Spacecraft(n, x, y) {}

// Destructor
SpaceProbe::~SpaceProbe() {}

// Mutator, prospects an asteroid on the same coordinate as the space probe
// @precond: an asteroid exists and has not been visited yet
// @postcond: the space probe will not prospect the same asteroid anymore
// @param: AsteroidField, to turn on a flag of an visited asteroid
void SpaceProbe::visit(AsteroidList& field) { prospectAsteroid(field); }

// Mutator, prospects an asteroid on the same coordinate as the space probe
// @precond: an asteroid exists and has not been visited yet
// @postcond: the space probe will not prospect the same asteroid anymore
// @param: AsteroidField, to turn on a flag of an visited asteroid
void SpaceProbe::prospectAsteroid(AsteroidList& field) {
	int closest = searchField(field);

	// Check whether the space probe and an asteroid are on the same coordinate
	if (getDistance(field, closest) == 0) {
		if (field.getAsteroid(closest).isPrecious()) {
			precious_list += (field.getAsteroid(closest));
		}
		field.visit(closest);
		visited++;
		prospected++;
	}
	else { cout << "You are too far away from an asteroid." << endl; }
}

// Accessor, gets a type of spacecraft
// @param: none
// @return: char
char SpaceProbe::getType() const { return 'P'; }

// Accessor, gets number of asteroids that a spaceprobe has prospected
// @param: none
// @return: int
int SpaceProbe::getVisited() { return visited; }

// Accessor, tells formatted space probe data by string
// @param: none
// @return: string
string SpaceProbe::toString() const {
	stringstream stream("");
	stream << Spacecraft::toString() << " -N/A- |";
	return stream.str();
}

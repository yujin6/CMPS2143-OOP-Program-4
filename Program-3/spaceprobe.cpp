#include "spaceprobe.h"
#include <iostream>
using namespace std;

// Default Constructor
// @param: none
SpaceProbe::SpaceProbe() : Spacecraft() {
}

// Copy Constructor
// @param: Spaceship to be copied from
SpaceProbe::SpaceProbe(const SpaceProbe &other) : Spacecraft(other.x_position,
	other.y_position) {
	// total distance and visited asteroids has to be overridden from
	// spacecraft's parameterized constructor
	total_distance = other.total_distance;
	visited_asteroids = other.visited_asteroids;
	for (int i = 0; i < other.precious_list.getLength(); i++) {
		precious_list.addAsteroid(other.precious_list.getAsteroid(i));
	}
}

// Parameterized Constructor with user defined coordinates
// @param: 2 ints, to set x and y coordinates
SpaceProbe::SpaceProbe(int x, int y) : Spacecraft(x, y) {
}

// Destructor
SpaceProbe::~SpaceProbe() {
}

// Mutator, prospects an asteroid on the same coordinate as the space probe
// @precond: an asteroid exists and has not been visited yet
// @postcond: the space probe will not prospect the same asteroid anymore
// @param: AsteroidField, to turn on a flag of an visited asteroid
void SpaceProbe::prospectAsteroid(AsteroidList& field) {
	int closest_asteroid = searchField(field);

	// Check whether the spaceprobe and an asteroid are on the same coordinate
	if (getDistance(field, closest_asteroid) == 0) {
		if (field.getAsteroid(closest_asteroid).isPrecious()) {
			precious_list.addAsteroid(field.getAsteroid(closest_asteroid));
		}
		field.visit(closest_asteroid);
		visited_asteroids++;
	}
	else { cout << "You are too far away from an asteroid." << endl; }
}

// Accessor, provides AsteroidList for spaceship to collect precious metals
AsteroidList SpaceProbe::getPreciousAsteroidList() {
	return precious_list;
}

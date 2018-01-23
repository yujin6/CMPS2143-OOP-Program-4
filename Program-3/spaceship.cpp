#include "spaceship.h"
#include <iostream>
#include <string>
using namespace std;

// Default Constructor
// @param: none
Spaceship::Spaceship() : Spacecraft() {
	collectable_size = DEFAULT_SIZE;
	total_size = 0;
}

// Copy Constructor
// @param: Spaceship to be copied from
Spaceship::Spaceship(const Spaceship &other) : Spacecraft(other.x_position,
	other.y_position) {
	// total distance and visited asteroids has to be overridden from
	// spacecraft's parameterized constructor
	total_distance = other.total_distance;
	visited_asteroids = other.visited_asteroids;
	collectable_size = other.collectable_size;
	total_size = other.total_size;
}

// Parameterized Constructor with user defined coordinates
// @param: 2 ints, to set x and y coordinates
Spaceship::Spaceship(int x, int y) : Spacecraft(x, y) {
	collectable_size = DEFAULT_SIZE;
	total_size = 0;
}

// Destructor
Spaceship::~Spaceship() {

}

// Mutator, sets a maximum collectable size of a spaceship
// @precond: the collectable size is not set
// @postcond: the collectable size is set with positive number
// @param: float, to set collectable size
void Spaceship::setSize(float size) {
	collectable_size = validate(size);
}

// Mutator, collects an asteroid on the same coordinate as the spaceship
// @precond: the spaceship is on the same coordinate as the asteroid,
//			 the asteroid has not been collected yet and is collectable size
// @postcond: the spaceship will not collect the same asteroid anymore
// @param: AsteroidField, to turn on a flag of an collected asteroid
void Spaceship::collectAsteroid(AsteroidList& field) {
	int closest_asteroid = searchField(field);

	// Check whether the spaceship and an asteroid are on the same coordinate
	if (getDistance(field, closest_asteroid) == 0) {

		// Check whether the asteroid is collectable size
		if (field.getAsteroid(closest_asteroid).getSize() <= collectable_size) {
			field.visit(closest_asteroid);
			visited_asteroids++;
			total_size += field.getAsteroid(closest_asteroid).getSize();
		}
		else { cout << "The asteroid is too large to be collected." << endl; }
	}
	else { cout << "You are too far away from an asteroid." << endl; }
}

// Mutator, blasts an asteroid on the same coordinate as the spaceship
// @precond: the spaceship is on the same coordinate as the asteroid,
//			 the asteroid has not been collected, and its size is not collectable
// @postcond: the spaceship will not collect the blasted asteroid,
//			  the fragments of the asteroid will be added to the asteroid list,
//			  and spaceship will be damaged when the fragment hits the spaceship
// @param: AsteroidList, to add fragments of the blasted asteroid
void Spaceship::blastAsteroid(AsteroidList& field) {
	// Generate a random number between 0 and 1
	double fraction = ((double)rand() / (RAND_MAX));
	int closest_asteroid = searchField(field);
	float size;

	// Check whether the spaceship and an asteroid are on the same coordinate
	if (getDistance(field, closest_asteroid) == 0) {

		// Remove the original asteroid by setting a flag on
		field.visit(closest_asteroid);

		// Adds first fragment of the blasted asteroid
		size = field.getAsteroid(closest_asteroid).getSize() * fraction;
		addFragment(field, size);

		// Adds second fragment of the blasted asteroid
		size = field.getAsteroid(closest_asteroid).getSize() - size;
		addFragment(field, size);
	}
	else { cout << "You are too far away from an asteroid." << endl; }
}

// Accessor, gets collectable size of asteroids that a spaceship can collect
// @param: none
// @return: float
float Spaceship::getCollectableSize() const { return collectable_size; }

// Accessor, gets total size of asteroids that a spaceship has collected
// @param: none
// @return: float
float Spaceship::getTotalSize() const { return total_size; }

// Prevents user defined size to be negative
// @param: float
// @return: float
float Spaceship::validate(float size) {
	if (size < 0) { size = size * -1; }
	return size;
}

// Adds a fragment of the blasted asteroid to the asteroid list
// @param: AsteroidList and float, the size of the asteroid to be added
void Spaceship::addFragment(AsteroidList& field, float size) {
	// Generate a random coordinate for the fragment
	int x = rand() % 100;
	int y = rand() % 100;
	char metal = 'P';

	field.addAsteroid(x, y, size, metal);

	// Check if the new asteroid hits the spaceship
	if (x == x_position && y == y_position) {
		cout << "An asteroid has hit the spaceship and damaged!" << endl;
		system("pause");
	}
}

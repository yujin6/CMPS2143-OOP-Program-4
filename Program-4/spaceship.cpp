#include "spaceship.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

// Default Constructor
// @param: none
Spaceship::Spaceship() : Spacecraft() {
	collectable_size = DEFAULT_SIZE;
	total_size = 0;
}

// Copy Constructor
// @param: Spaceship to be copied from
Spaceship::Spaceship(const Spaceship &other) : Spacecraft(other) {
	collectable_size = other.collectable_size;
	total_size = other.total_size;
}

// Parameterized Constructor with user defined name
// @param: string, to set name
Spaceship::Spaceship(string n) : Spacecraft(n) {
	collectable_size = DEFAULT_SIZE;
	total_size = 0;
}

// Parameterized Constructor with user defined coordinates
// @param: 2 ints, to set x and y coordinates
Spaceship::Spaceship(int x, int y) : Spacecraft(x, y) {
	collectable_size = DEFAULT_SIZE;
	total_size = 0;
}

// Parameterized Constructor with user defined name and coordinates
// @param: string and 2 ints, to set name and x and y coordinates
Spaceship::Spaceship(string n, int x, int y) : Spacecraft(n, x, y) {
	collectable_size = DEFAULT_SIZE;
	total_size = 0;
}

// Destructor
Spaceship::~Spaceship() {}

// Overload Operator *, blasts an asteroid on the same coordinate as the spaceship
// @precond: the spaceship is on the same coordinate as the asteroid,
//			 the asteroid has not been collected, and its size is not collectable
// @postcond: the spaceship will not collect the blasted asteroid,
//			  the fragments of the asteroid will be added to the asteroid list,
//			  and spaceship will be damaged when the fragment hits the spaceship
// @param: AsteroidField, to turn on a flag of an visited asteroid
void Spaceship::operator *(AsteroidList& field) { blastAsteroid(field); }

// Mutator, sets a maximum collectable size of a spaceship
// @precond: the collectable size is not set
// @postcond: the collectable size is set with positive number
// @param: float, to set collectable size
void Spaceship::setSize(float size) { collectable_size = validate(size); }

// Mutator, collects an asteroid on the same coordinate as the spaceship
// @precond: the spaceship is on the same coordinate as the asteroid,
//			 the asteroid has not been collected yet and is collectable size
// @postcond: the spaceship will not collect the same asteroid anymore
// @param: AsteroidField, to turn on a flag of an collected asteroid
void Spaceship::visit(AsteroidList& field) { collectAsteroid(field); }

// Mutator, collects an asteroid on the same coordinate as the spaceship
// @precond: the spaceship is on the same coordinate as the asteroid,
//			 the asteroid has not been collected yet and is collectable size
// @postcond: the spaceship will not collect the same asteroid anymore
// @param: AsteroidField, to turn on a flag of an collected asteroid
void Spaceship::collectAsteroid(AsteroidList& field) {
	int closest = searchField(field);

	// Check whether the spaceship and an asteroid are on the same coordinate
	if (getDistance(field, closest) == 0) {

		// Check whether the asteroid is collectable size
		if (field.getAsteroid(closest).getSize() <= collectable_size) {
			field.visit(closest);
			visited++;
			collected++;
			total_size += field.getAsteroid(closest).getSize();
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
	AsteroidList fragments;
	// Generate a random number between 0 and 1
	float fraction = ((float)rand() / (RAND_MAX));
	int closest = searchField(field);
	float size;

	// Check whether the spaceship and an asteroid are on the same coordinate
	if (getDistance(field, closest) == 0) {
		field.visit(closest);

		// Adds first fragment of the blasted asteroid
		size = field.getAsteroid(closest).getSize() * fraction;
		addFragment(field, size);

		// Adds second fragment of the blasted asteroid
		size = field.getAsteroid(closest).getSize() - size;
		addFragment(field, size);

		checkDamage(field, closest);
	}
	else { cout << "You are too far away from an asteroid." << endl; }
}

// Accessor, gets a type of spacecraft
// @param: none
// @return: char
char Spaceship::getType() const { return 'S'; }

// Accessor, gets a maximum collectable size of a spaceship
float Spaceship::getSize() const { return collectable_size; }

// Accessor, gets number of asteroids that a spaceship has collected
// @param: none
// @return: int
int Spaceship::getVisited() { return visited; }

// Accessor, gets collectable size of asteroids that a spaceship can collect
// @param: none
// @return: float
float Spaceship::getCollectableSize() const { return collectable_size; }

// Accessor, gets total size of asteroids that a spaceship has collected
// @param: none
// @return: float
float Spaceship::getTotalSize() const { return total_size; }

// Accessor, tells formatted space probe data by string
// @param: none
// @return: string
string Spaceship::toString() const {
	stringstream stream("");
	stream << Spacecraft::toString() << " ";
	stream << setw(5) << right << fixed << setprecision(1) << total_size;
	stream << " |";
	return stream.str();
}

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
	Asteroid temp(x, y, size, metal);

	field += temp;
}

#include "asteroidlist.h"
#include <iostream>
using namespace std;

// Default Constructor
// @param: none
AsteroidList::AsteroidList() {
	asteroid_list = new Asteroid[MAX_LENGTH];
	length = 0;
}
// Copy Constructor
// @param: AsteroidList to be copied from
AsteroidList::AsteroidList(const AsteroidList &other) {
	asteroid_list = new Asteroid[MAX_LENGTH];
	for (int i = 0; i < other.length; i++) {
		asteroid_list[i].copy(other.asteroid_list[i]);
	}
	length = other.length;
}

// Parameterized Constructor with user defined length
// @param: int, to set maximum length
AsteroidList::AsteroidList(int max_length) {
	asteroid_list = new Asteroid[max_length];
	length = 0;
}

// Destructor
AsteroidList::~AsteroidList() {
	delete[] asteroid_list;
}

// Mutator, add an asteroid
// @precond: an asteroid already exists, and the asteroid list is not full yet
// @postcond: an asteroid in the asteroid list can now be identified by index
// @param: 2 ints for x and y coordinates, float for size, char for metal
void AsteroidList::addAsteroid(int x, int y, float size, char metal) {
	if (length < MAX_LENGTH) {
		asteroid_list[length].set(x, y, size, metal);
		length++;
	}
	else { cout << "The asteroid list is full." << endl; }
}

// Mutator, adds an asteroid
// @precond: an asteroid already exists, and the asteroid list is not full yet
// @postcond: an asteroid in the asteroid list can now be identified by index
// @param: Asteroid to be copied from
void AsteroidList::addAsteroid(const Asteroid &other) {
	int x = other.getX();
	int y = other.getY();
	float size = other.getSize();
	char metal;
	if (other.isPrecious()) { metal = 'P'; }
	else { metal = 'N'; }

	addAsteroid(x, y, size, metal);
}

// Mutator, sets a flag on when an asteroid has been visited
// @precond: an asteroid has not been visited yet
// @postcond: an asteroid doesn't have to be visited anymore
// @param: int for index of an asteroid in the list
void AsteroidList::visit(int index) {
	asteroid_list[index].visit();
}

// Accessor, obtains a copy of an asteroid's data
// @param: int, to identify the index
// @return: copy of Asteroid
Asteroid AsteroidList::getAsteroid(int index) const {
	return asteroid_list[index];
}

// Accessor, gets the number of asteroids
// @param: none
// @return: int
int AsteroidList::getLength() const {
	return length;
}

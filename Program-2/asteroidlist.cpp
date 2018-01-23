#include "asteroidlist.h"
using namespace std;

// Default Constructor
// @param: none
AsteroidList::AsteroidList() {
	Asteroid* field = new Asteroid[MAX_LENGTH];
	asteroid_list = field;
	length = 0;
}
// Copy Constructor
// @param: AsteroidList to be copied from
AsteroidList::AsteroidList(AsteroidList &other) {
	asteroid_list = other.asteroid_list;
	length = other.length;
}

// Parameterized Constructor with user defined length
// @param: int, to set maximum length
AsteroidList::AsteroidList(int max_length) {
	Asteroid* field = new Asteroid[max_length];
	asteroid_list = field;
	length = 0;
}

// Destructor
AsteroidList::~AsteroidList() {
	delete[] asteroid_list;
}

// Mutator, add an asteroid
// @param: 2 ints for x and y coordinates, float for size
void AsteroidList::addAsteroid(int x, int y, float size) {
	asteroid_list[length].set(x, y, size);
	length++;
}

// Mutator, sets a flag on when an asteroid has been collected
// @param: int for index of an asteroid in the list
void AsteroidList::collect(int index) {
	asteroid_list[index].collect();
}

// Accessor, obtains coordinates of an asteroid
// @param: 2 ints for x and y coordinates, 1 int for index
// @return: void (pass by reference)
void AsteroidList::getCoordinates(int &x, int &y, int index) const {
	x = asteroid_list[index].getX();
	y = asteroid_list[index].getY();
}

// Accessor, obtains size of an asteroid
// @param: int for index of an asteroid in the list
// @return: float
float AsteroidList::getSize(int index) const {
	return asteroid_list[index].getSize();
}

// Accessor, obtains whether an asteroid has been collected or not
// @param: int for index of an asteroid in the list
// @return: bool
bool AsteroidList::isCollected(int index) const {
	return asteroid_list[index].isCollected();
}

// Accessor, gets the number of asteroids
// @param: none
// @return: int
int AsteroidList::getLength() const {
	return length;
}

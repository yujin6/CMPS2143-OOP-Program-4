#pragma once
#include "asteroid.h"
using namespace std;

class AsteroidList {
public:

	const int MAX_LENGTH = 255;

	// Default Constructor
	AsteroidList();

	// Copy Constructor
	AsteroidList(AsteroidList &other);

	// Parameterized Constructor with user defined length
	AsteroidList(int max_length);

	// Destructor
	~AsteroidList();

	// Mutator, adds an asteroid
	void addAsteroid(int x, int y, float size);

	// Mutator, sets a flag on when an asteroid has been collected
	void collect(int index);

	// Accessor, obtains coordinates of an asteroid
	void getCoordinates(int &x, int &y, int index) const;

	// Accessor, obtains size of an asteroid
	float getSize(int index) const;

	// Accessor, obtains whether an asteroid has been collected or not
	bool isCollected(int index) const;

	// Accessor, gets the number of asteroids
	int getLength() const;

private:
	Asteroid* asteroid_list;
	int length;
};
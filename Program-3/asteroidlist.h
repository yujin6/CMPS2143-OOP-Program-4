#pragma once
#include "asteroid.h"
using namespace std;

class AsteroidList {
public:

	const int MAX_LENGTH = 255;

	// Default Constructor
	AsteroidList();

	// Copy Constructor
	AsteroidList(const AsteroidList &other);

	// Parameterized Constructor with user defined length
	AsteroidList(int max_length);

	// Destructor
	~AsteroidList();

	// Mutator, adds an asteroid
	void addAsteroid(int x, int y, float size, char metal);

	// Mutator, adds an asteroid
	void addAsteroid(const Asteroid &other);

	// Mutator, sets a flag on when an asteroid has been visited
	void visit(int index);

	// Accessor, obtains a copy of an asteroid's data
	Asteroid getAsteroid(int index) const;

	// Accessor, gets the number of asteroids
	int getLength() const;

private:
	Asteroid* asteroid_list;
	int length;
};
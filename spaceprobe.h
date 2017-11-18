#pragma once
#include "spacecraft.h"
#include "asteroidlist.h"
using namespace std;

class SpaceProbe : public Spacecraft {
public:

	// Default Constructor
	SpaceProbe();

	// Copy Constructor
	SpaceProbe(const SpaceProbe &other);

	// Parameterized Constructor with user defined name
	SpaceProbe(string n);

	// Parameterized Constructor with user defined coordinates
	SpaceProbe(int x, int y);

	// Parameterized Constructor with user defined name and coordinates
	SpaceProbe(string n, int x, int y);

	// Destructor
	~SpaceProbe();

	// Mutator, prospects an asteroid on the same coordinate as the space probe
	void visit(AsteroidList& field);

	// Mutator, prospects an asteroid on the same coordinate as the space probe
	void prospectAsteroid(AsteroidList& field);

	// Accessor, gets a type of spacecraft
	char getType() const;

	// Accessor, gets number of asteroids that a spaceprobe has prospected
	int getVisited();

	// Accessor, tells formatted space probe data by string
	string toString() const;
};
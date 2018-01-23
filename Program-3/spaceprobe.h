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

	// Parameterized Constructor with user defined coordinates
	SpaceProbe(int x, int y);

	// Destructor
	~SpaceProbe();

	// Mutator, prospects an asteroid on the same coordinate as the space probe
	void prospectAsteroid(AsteroidList& field);

	// Accessor, provides AsteroidList for spaceship to collect precious metals
	AsteroidList getPreciousAsteroidList();

private:

	AsteroidList precious_list; // List of asteroids that contains precious metals

};
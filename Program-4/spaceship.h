#pragma once
#include "spacecraft.h"
#include "asteroidlist.h"
using namespace std;

class Spaceship : public Spacecraft {
public:

	const float DEFAULT_SIZE = 10;

	// Default Constructor
	Spaceship();

	// Copy Constructor
	Spaceship(const Spaceship &other);

	// Parameterized Constructor with user defined name
	Spaceship(string n);

	// Parameterized Constructor with user defined coordinates
	Spaceship(int x, int y);

	// Parameterized Constructor with user defined name and coordinates
	Spaceship(string n, int x, int y);

	// Destructor
	~Spaceship();

	// Overload Operator *, blasts an asteroid on the same coordinate as the spaceship
	void operator *(AsteroidList& field);

	// Mutator, sets a maximum collectable size of a spaceship
	void setSize(float size);

	// Mutator, collects an asteroid on the same coordinate as the spaceship
	void visit(AsteroidList& field);

	// Mutator, collects an asteroid on the same coordinate as the spaceship
	void collectAsteroid(AsteroidList& field);

	// Mutator, blasts an asteroid on the same coordinate as the spaceship
	void blastAsteroid(AsteroidList& field);

	// Accessor, gets a type of spacecraft
	char getType() const;

	// Accessor, gets a maximum collectable size of a spaceship
	float getSize() const;

	// Accessor, gets number of asteroids that a spaceship has collected
	int getVisited();

	// Accessor, gets collectable size of asteroids that a spaceship can collect
	float getCollectableSize() const;

	// Accessor, gets total size of asteroids that a spaceship has collected
	float getTotalSize() const;

	// Accessor, tells formatted spaceship data by string
	string toString() const;

private:

	// Prevents user defined size to be negative
	float validate(float size);

	// Adds a fragment of the blasted asteroid to the asteroid list
	void addFragment(AsteroidList& field, float size);

	float collectable_size; // Determines maximum collectable size of a spaceship
	float total_size; // Total size of asteroids collected by a spaceship
};

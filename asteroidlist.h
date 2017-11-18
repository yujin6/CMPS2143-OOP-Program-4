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

	// Overload Operator = to copy
	void operator = (const AsteroidList &other);

	// Overload Operator +, adds an Asteroid
	AsteroidList operator + (const Asteroid &other);

	// Overload Operator +=, adds an Asteroid
	void AsteroidList::operator += (const Asteroid &other);

	// Mutator, adds an asteroid
	void addAsteroid(const Asteroid &other);

	// Mutator, adds an asteroid
	void addAsteroid(int x, int y, float size, char metal);

	// Mutator, sets a flag on when an asteroid has been visited
	void visit(int index);

	// Accessor, obtains a copy of an asteroid's data
	Asteroid getAsteroid(int index) const;

	// Accessor, gets the number of asteroids
	int getLength() const;

	// Accessor, tells formatted asteroid list data by string
	string toString() const;

private:
	Asteroid* asteroid_list; // array of asteroids
	int length; // Number of asteroids
};
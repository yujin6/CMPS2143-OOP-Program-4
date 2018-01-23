#pragma once
#include "spaceobject.h"
using namespace std;

class Asteroid : public SpaceObject {
public:

	const float DEFAULT_SIZE = 0;

	// Default Constructor
	Asteroid();

	// Copy Constructor
	Asteroid(const Asteroid &other);

	// Parameterized Constructor with user defined size
	Asteroid(float size);

	// Parameterized Constructor with user defined coordinates
	Asteroid(int x, int y);

	// Parameterized Constructor with user defined coordinates and size
	Asteroid(int x, int y, float size);

	// Destructor
	~Asteroid();

	// Mutator, copies an asteroid
	void copy(const Asteroid &other);

	// Mutator, sets an asteroid with user defined coordinates, size and metal
	void set(int x, int y, float size, char metal);

	// Mutator, sets a flag on when an asteroid has been visited by a spacecraft
	void visit();

	// Accessor, gets size of an asteroid
	float getSize() const;

	// Accessor, allows an asteroid to know if it has been visited by a spacecraft
	bool isVisited() const;

	// Accessor, tells spacecraft whether an asteroid contains precious metal
	bool isPrecious() const;

private:

	// Prevents user defined size to be negative
	float validate(float size);

	float size; // Determines size of an asteroid
	bool visited; // Flags whether an asteroid has been visited by a spacecraft
	bool precious; // Flags when an asteroid contains precious metal
};
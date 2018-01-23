#pragma once
using namespace std;

class Asteroid {
public:

	const float DEFAULT_SIZE = 10;

	// Default Constructor
	Asteroid();

	// Copy Constructor
	Asteroid(Asteroid &other);

	// Parameterized Constructor with user defined size
	Asteroid(float size);

	// Parameterized Constructor with user defined coordinates
	Asteroid(int x, int y);

	// Parameterized Constructor with user defined coordinates and size
	Asteroid(int x, int y, float size);

	// Destructor
	~Asteroid();

	// Mutator, sets an asteroid with user defined coordinates and size
	void set(int x, int y, float size);

	// Mutator, sets a flag on when an asteroid has been collected
	void collect();

	// Accessor, gets x-coordinate of an asteroid
	int getX() const;

	// Accessor, gets y-coordinate of an asteroid
	int getY() const;

	// Accessor, gets size of an asteroid
	float getSize() const;

	// Accessor, allows an asteroid to know if it has been collected
	bool isCollected() const;

private:
	int x_position; // Determines x-coordinate of an asteroid
	int y_position; // Determines y-coordinate of an asteroid
	float size; // Determines size of an asteroid
	bool collected;
};
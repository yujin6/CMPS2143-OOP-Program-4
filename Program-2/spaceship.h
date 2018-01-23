#pragma once
#include "asteroidlist.h"
#include <string>
using namespace std;

class Spaceship {
public:

	const float DEFAULT_SIZE = 10;

	// Default Constructor
	Spaceship();

	// Copy Constructor
	Spaceship(Spaceship &other);

	// Parameterized Constructor with user defined coordinates
	Spaceship(int x, int y);

	// Destructor
	~Spaceship();

	// Mutator, sets a maximum collectable size of a spaceship
	void setSize(float size);

	// Mutator, moves a spaceship to given coordinates
	void move(int x, int y);

	// Mutator, collects an asteroid on the same coordinate as the spaceship
	void collectAsteroid(AsteroidList& field);

	// Mutator, blasts an asteroid on the same coordinate as the spaceship
	void blastAsteroid(AsteroidList& field);

	// Accessor, searches a closest asteroid
	int searchField(const AsteroidList& field) const;

	// Accessor, gets a distance between a spaceship and given coordinates
	double getDistance(int x, int y) const;

	// Accessor, gets a distance between a spaceship and an asteroid
	double getDistance(const AsteroidList& field, int index) const;

	// Accessor, gets a direction from a spaceship to an asteroid
	string getDirection(const AsteroidList& field, int index) const;

	// Accessor, gets current coordinates of a spaceship
	void locate(int &x, int &y) const;

	// Accessor, gets number of asteroids that a spaceship has collected
	int getCollectedAsteroids() const;

	// Accessor, gets collectable size of asteroids that a spaceship can collect
	float getCollectableSize() const;

	// Accessor, gets total size of asteroids that a spaceship has collected
	float getTotalSize() const;

	// Accessor, gets total distance that a spaceship has travelled
	double getTotalDistance() const;

private:
	int x_position; // Determines x-coordinate of a spaceship
	int y_position; // Determines y-coordinate of a spaceship
	int collected_asteroids; // Number of asteroids collected by a spaceship
	float collectable_size; // Determines maximum collectable size of a spaceship
	float total_size; // Total size of asteroids collected by a spaceship
	double total_distance; // Total Distance travelled by a spaceship
	
};
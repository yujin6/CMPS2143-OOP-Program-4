#pragma once
#include <string>
#include <cmath>
#include "spaceobject.h"
#include "asteroidlist.h"
using namespace std;

class Spacecraft : public SpaceObject {
public:
	// Default Constructor
	Spacecraft();

	// Copy Constructor
	Spacecraft(const Spacecraft &other);

	// Parameterized Constructor with user defined coordinates
	Spacecraft(int x, int y);

	// Destructor
	~Spacecraft();

	// Mutator, moves a spacecraft to given coordinates
	void move(int x, int y);

	// Accessor, searches a closest asteroid
	int searchField(const AsteroidList& field) const;

	// Accessor, gets a distance between a spaceship and given coordinates
	double getDistance(int x, int y) const;

	// Accessor, gets a distance between a spaceship and an asteroid
	double getDistance(const AsteroidList& field, int index) const;

	// Accessor, gets a direction from a spaceship to an asteroid
	string getDirection(const AsteroidList& field, int index) const;

	// Accessor, gets total distance that a spaceship has travelled
	double getTotalDistance() const;

	// Accessor, gets number of asteroids that a spaceship has collected
	int getVisitedAsteroids() const;

protected:
	double total_distance; // Total Distance travelled by a spacecraft
	int visited_asteroids; // Number of asteroids visited by a spacecraft
};
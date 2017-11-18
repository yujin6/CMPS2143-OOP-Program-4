#pragma once
#include "spaceobject.h"
#include "asteroidlist.h"
using namespace std;

class Spacecraft : public SpaceObject {
public:
	// Default Constructor
	Spacecraft();

	// Copy Constructor
	Spacecraft(const Spacecraft &other);

	// Parameterized Constructor with user defined name
	Spacecraft(string n);

	// Parameterized Constructor with user defined coordinates
	Spacecraft(int x, int y);

	// Parameterized Constructor with user defined name and coordinates
	Spacecraft(string n, int x, int y);

	// Destructor
	~Spacecraft();

	// Overload Operator =, copies a spacecraft by deep copy
	void operator =(const Spacecraft &other);

	// Overload Operator <<, visits an asteroid on the same coordinate
	void operator +(AsteroidList& field);

	// Mutator, moves a spacecraft to given coordinates
	void move(int x, int y);

	// Mutator, visits an asteroid on the same coordinate as the space craft
	virtual void visit(AsteroidList& field);

	// Mutator, checks whether the spacecraft has hit by a moving asteroid
	void checkDamage(const AsteroidList& field, int blasted);

	// Mutator, sets number of asteroids that space probes to prospect
	static void setMaxProspect(int prospect);

	// Mutator, sets number of asteroids that spaceships to collect
	static void setMaxCollect(int collect);

	// Accessor, searches a closest asteroid
	int searchField(const AsteroidList& field) const;

	// Accessor, gets a type of spacecraft
	virtual char getType() const;

	// Accessor, gets a distance between a spacecraft and given coordinates
	double getDistance(int x, int y) const;

	// Accessor, gets a distance between a spacecraft and an asteroid
	double getDistance(const AsteroidList& field, int index) const;

	// Accessor, gets a direction from a spacecraft to an asteroid
	string getDirection(const AsteroidList& field, int index) const;

	// Accessor, gets total distance that a spacecraft has travelled
	double getTotalDistance() const;

	// Accessor, provides AsteroidList for spaceship to collect precious metals
	static AsteroidList getPreciousAsteroidList();

	// Accessor, gets number of asteroids that space probes to prospect
	static int getMaxProspect();

	// Accessor, gets number of asteroids that space probes has prospected
	static int getProspected();

	// Accessor, gets number of asteroids that spaceships to collect
	static int getMaxCollect();

	// Accessor, gets number of asteroids that spaceships has collected
	static int getCollected();

	// Accessor, tells formatted precious list data by string
	static string getList();

	// Accessor, tells formatted spacecraft data by string
	virtual string toString() const;

protected:
	int visited;				// Number of asteroids visited by a spacecraft
	double total_distance;		// Total Distance travelled by a spacecraft
	static int max_prospect;	// Total number of asteroids to prospect by space probes
	static int prospected;		// Total number of asteroids prospected by space probes
	static int max_collect;		// Total number of asteroids to collect by spaceships
	static int collected;		// Total number of asteroids collected by spaceships
	static AsteroidList precious_list; // List of asteroids that contains precious metals

private:
	// Calculates the movement of asteroid when blasted, for checkDamage purpose
	bool isDamaged(const AsteroidList& field, int blasted, int fragment);
};
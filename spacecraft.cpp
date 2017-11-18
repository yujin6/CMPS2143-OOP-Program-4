#include "spacecraft.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#define PI 3.1415926536
using namespace std;

// Default Constructor
// @param: none
Spacecraft::Spacecraft() : SpaceObject() {
	name = "Spacecraft";
	visited = 0;
	total_distance = 0;
}

// Copy Constructor
// @param: Spaceship to be copied from
Spacecraft::Spacecraft(const Spacecraft &other) : SpaceObject(other) {
	operator=(other);
}

// Parameterized Constructor with user defined name
// @param: string, to set name
Spacecraft::Spacecraft(string n) : SpaceObject() {
	name = n;
	visited = 0;
	total_distance = 0;
}

// Parameterized Constructor with user defined coordinates
// @param: 2 ints, to set x and y coordinates
Spacecraft::Spacecraft(int x, int y) : SpaceObject(x, y) {
	name = "Spacecraft";
	visited = 0;
	total_distance = 0;
}

// Parameterized Constructor with user defined name and coordinates
// @param: string and 2 ints, to set name and x and y coordinates
Spacecraft::Spacecraft(string n, int x, int y) : SpaceObject(x, y) {
	name = n;
	visited = 0;
	total_distance = 0;
}

// Destructor
Spacecraft::~Spacecraft() {}

// Overload Operator =, copies a spacecraft by deep copy
// @precond: an asteroid already exists
// @postcond: all the parameters of the asteroid is copied
// @param: Asteroid to be copied from
void Spacecraft::operator =(const Spacecraft &other) {
	setCoordinates(other.x, other.y);
	name = other.name;
	visited = other.visited;
	total_distance = other.total_distance;
}

// Overload Operator <<, visits an asteroid on the same coordinate
// @precond: an asteroid exists and has not been visited yet
// @postcond: the spacecraft will not prospect the same asteroid anymore
// @param: AsteroidField, to turn on a flag of an visited asteroid
void Spacecraft::operator +(AsteroidList& field) { visit(field); }

// Mutator, moves a spacecraft to given coordinates
// @precond: the coordinates to be moved to is within the dimension
// @postcond: the total distance is accumulated
// @param: 2 ints, to set x and y coordinates
void Spacecraft::move(int x, int y) {
	total_distance += getDistance(x, y);
	setCoordinates(x, y);
}

// Mutator, visits an asteroid on the same coordinate as the spacecraft
// @precond: an asteroid exists and has not been visited yet
// @postcond: the spacecraft will not prospect the same asteroid anymore
// @param: AsteroidField, to turn on a flag of an visited asteroid
void Spacecraft::visit(AsteroidList& field) {
	int closest_asteroid = searchField(field);

	// Check whether the space craft and an asteroid are on the same coordinate
	if (getDistance(field, closest_asteroid) == 0) {
		field.visit(closest_asteroid);
	}
	else { cout << "You are too far away from an asteroid." << endl; }
}

// Mutator, checks whether the spacecraft has hit by a moving asteroid
// @precond: an asteroid has been blasted and created two fragments
// @postcond: if the asteroid hits the spacecraft, it will be damaged
// @param: AsteroidField and int, to identify which asteroid has been blasted
void Spacecraft::checkDamage(const AsteroidList& field, int blasted) {
	int fragment = field.getLength() - 2;

	while (fragment < field.getLength()) {
		if (isDamaged(field, blasted, fragment)) {
			cout << "| --- | " << SpaceObject::toString() << " | ---- | Damaged    | "
				<< setw(8) << left << name << " | -------- | ----------- |"	<< endl;
		}
		fragment++;
	}
}

// Mutator, sets number of asteroids that space probes to prospect
// @precond: maximum number to be prospected has not been set yet
// @postcond: space probes will not prospect more than maximum
// @param: int, to set maximum number of asteroids to be prospected
void Spacecraft::setMaxProspect(int prospect) { max_prospect = prospect; }

// Mutator, sets number of asteroids that spaceships to collect
// @precond: maximum number to be collected has not been set yet
// @postcond: spaceships will not collect more than maximum
// @param: int, to set maximum number of asteroids to be collected
void Spacecraft::setMaxCollect(int collect) { max_collect = collect; }

// Accessor, searches a closest asteroid
// @param: AsteroidList, to search a closest asteroid
// @return: int
int Spacecraft::searchField(const AsteroidList& field) const {

	// Largest possible distance within 100x100 grid is 142
	double min_distance = DIMENSION * sqrt(2);
	int index = -1;

	// Searches for minimum distance by linear search
	for (int i = 0; i < field.getLength(); i++) {

		// Skips the loop when an asteroid has already been visited
		if (!field.getAsteroid(i).isVisited()) {

			// Skips the loop when an asteroid is far
			if (getDistance(field, i) < min_distance) {
				min_distance = getDistance(field, i);
				index = i;
			}
		}
	}
	return index;
}

// Accessor, gets a type of spacecraft
// @param: none
// @return: char
char Spacecraft::getType() const { return 'C'; }

// Accessor, gets a distance between a spacecraft and given coordinates
// @param: 2 ints, x and y coordinates
// @return: double
double Spacecraft::getDistance(int x, int y) const {
	double distance = sqrt(pow(x - this->x, 2) + pow(y - this->y, 2));
	return distance;
}

// Accessor, gets a distance between a spacecraft and an asteroid
// @param: AsteroidList and int, to provide coordinates of an asteroid
// @return: double
double Spacecraft::getDistance(const AsteroidList& field, int index) const {
	double distance;
	int x, y;

	field.getAsteroid(index).getCoordinates(x, y);
	distance = getDistance(x, y);
	return distance;
}

// Accessor, gets a direction from a spacecraft to an asteroid
// @param: AsteroidList and int, to provide coordinates of an asteroid
// @return: string
string Spacecraft::getDirection(const AsteroidList& field, int index) const {
	string direction;
	double direction_in_degrees;
	int direction_in_zodiac;
	int x, y;

	field.getAsteroid(index).getCoordinates(x, y);
	direction_in_degrees = atan2((y - this->y), (x - this->x)) * 180 / PI;
	direction_in_zodiac = (int) floor(direction_in_degrees / 30) + 6;

	// Convert direction from number to words
	switch (direction_in_zodiac) {
	case 0:		direction = "Capricorn";	break;
	case 1:		direction = "Aquarius";		break;
	case 2:		direction = "Pisces";		break;
	case 3:		direction = "Aries";		break;
	case 4:		direction = "Taurus";		break;
	case 5:		direction = "Gemini";		break;
	case 6:		direction = "Cancer";		break;
	case 7:		direction = "Leo";			break;
	case 8:		direction = "Virgo";		break;
	case 9:		direction = "Libra";		break;
	case 10:	direction = "Scorpio";		break;
	case 11:	direction = "Sagittarius";	break;
	default:	direction = "Capricorn";	break;
	}

	return direction;
}

// Accessor, gets total distance that a spacecraft has travelled
// @param: none
// @return: double
double Spacecraft::getTotalDistance() const { return total_distance; }

// Accessor, provides AsteroidList for spaceship to collect precious metals
// @param: none
// @return: AsteroidList
AsteroidList Spacecraft::getPreciousAsteroidList() { return precious_list; }

// Accessor, gets number of asteroids that space probes to prospect
// @param: none
// @return: int
int Spacecraft::getMaxProspect() { return max_prospect; }

// Accessor, gets number of asteroids that space probes has prospected
// @param: none
// @return: int
int Spacecraft::getProspected() { return prospected; }

// Accessor, gets number of asteroids that spaceships to collect
// @param: none
// @return: int
int Spacecraft::getMaxCollect() { return max_collect; }

// Accessor, gets number of asteroids that spaceships has collected
// @param: none
// @return: int
int Spacecraft::getCollected() { return collected; }

// Accessor, tells formatted precious list data by string
// @param: none
// @return: string
string Spacecraft::getList() { return precious_list.toString(); }

// Accessor, tells formatted spacecraft data by string
// @param: none
// @return: string
string Spacecraft::toString() const {
	stringstream stream("");
	string type = "spacecraft";
	if (getType() == 'P') { type = "space probe"; }
	else if (getType() == 'S') { type = "spaceship "; }

	stream << "| " << setw(12) << left << type;
	stream << " | " << setw(8) << left << name;
	stream << " | " << setw(10) << SpaceObject::toString();
	stream << " | " << setw(7) << right << visited;
	stream << " | " << setw(14) << right << fixed << setprecision(2) << total_distance * 10;
	stream << " |";
	return stream.str();
}

// Calculates the movement of asteroid when blasted, for checkDamage purpose
// @param: AsteroidList, 2 ints for blasted asteroid and fragment asteroid
// @return: bool
bool Spacecraft::isDamaged(const AsteroidList& field, int blasted, int fragment) {
	int x1, x2, y1, y2;
	double x_slope, y_slope;
	bool damaged = false;

	field.getAsteroid(blasted).getCoordinates(x1, y1);
	field.getAsteroid(fragment).getCoordinates(x2, y2);
	x_slope = ((double)x - x1) / (x2 - x1);
	y_slope = ((double)y - y1) / (y2 - y1);

	if (x_slope > 0 && x_slope <= 1 && x_slope == y_slope) { damaged = true; }
	return damaged;
}

// Initialize static member variables and object
int Spacecraft::max_prospect = 0;
int Spacecraft::prospected = 0;
int Spacecraft::max_collect = 0;
int Spacecraft::collected = 0;
AsteroidList temp;
AsteroidList Spacecraft::precious_list = temp;
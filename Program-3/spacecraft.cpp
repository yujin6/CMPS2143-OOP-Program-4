#include "spacecraft.h"
#include <cmath>
#define PI 3.1415926536
using namespace std;

// Default Constructor
// @param: none
Spacecraft::Spacecraft() {
	setCoordinates(rand() % 100, rand() % 100);
	total_distance = 0;
	visited_asteroids = 0;
}

// Copy Constructor
// @param: Spaceship to be copied from
Spacecraft::Spacecraft(const Spacecraft &other) {
	setCoordinates(other.x_position, other.y_position);
	total_distance = other.total_distance;
	visited_asteroids = other.visited_asteroids;
}

// Parameterized Constructor with user defined coordinates
// @param: 2 ints, to set x and y coordinates
Spacecraft::Spacecraft(int x, int y) {
	setCoordinates(x, y);
	total_distance = 0;
	visited_asteroids = 0;
}

// Destructor
Spacecraft::~Spacecraft() {

}

// Mutator, moves a spacecraft to given coordinates
// @precond: the coordinates to be moved to is within the dimension
// @postcond: the total distance is accumulated
// @param: 2 ints, to set x and y coordinates
void Spacecraft::move(int x, int y) {
	total_distance += getDistance(x, y);
	setCoordinates(x, y);
}

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

// Accessor, gets a distance between a spacecraft and given coordinates
// @param: 2 ints, x and y coordinates
// @return: double
double Spacecraft::getDistance(int x, int y) const {
	double distance = sqrt(pow(x - x_position, 2) + pow(y - y_position, 2));
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
	direction_in_degrees = atan2((y - y_position), (x - x_position)) * 180 / PI;
	direction_in_zodiac = floor(direction_in_degrees / 30) + 6;

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

// Accessor, gets number of asteroids that a spaceship has collected
// @param: none
// @return: int
int Spacecraft::getVisitedAsteroids() const { return visited_asteroids; }

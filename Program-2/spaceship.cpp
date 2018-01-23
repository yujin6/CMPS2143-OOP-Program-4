#include "spaceship.h"
#include <iostream>
#include <string>
#include <cmath>
#define PI 3.1415926536
using namespace std;

// Default Constructor
// @param: none
Spaceship::Spaceship() {
	x_position = rand() % 100;
	y_position = rand() % 100;
	collected_asteroids = 0;
	collectable_size = DEFAULT_SIZE;
	total_size = 0;
	total_distance = 0;
}

// Copy Constructor
// @param: Spaceship to be copied from
Spaceship::Spaceship(Spaceship &other) {
	x_position = other.x_position;
	y_position = other.y_position;
	collected_asteroids = other.collected_asteroids;
	collectable_size = other.collectable_size;
	total_size = other.total_size;
	total_distance = other.total_distance;
}

// Parameterized Constructor with user defined coordinates
// @param: 2 ints, to set x and y coordinates
Spaceship::Spaceship(int x, int y) {
	x_position = x;
	y_position = y;
	collected_asteroids = 0;
	collectable_size = DEFAULT_SIZE;
	total_size = 0;
	total_distance = 0;
}

// Destructor
Spaceship::~Spaceship() {

}

// Mutator, sets a maximum collectable size of a spaceship
// @param: float, to set collectable size
void Spaceship::setSize(float size) {
	collectable_size = size;
}

// Mutator, moves a spaceship to given coordinates
// @param: 2 ints, to set x and y coordinates
void Spaceship::move(int x, int y) {
	total_distance += getDistance(x, y);
	x_position = x;
	y_position = y;
}

// Mutator, collects an asteroid on the same coordinate as the spaceship
// @param: AsteroidField, to turn on a flag of an collected asteroid
void Spaceship::collectAsteroid(AsteroidList& field) {
	int closest_asteroid = searchField(field);

	// Check whether the spaceship and an asteroid are on the same coordinate
	if (getDistance(field, closest_asteroid) == 0) {

		// Check whether the asteroid is collectable size
		if (field.getSize(closest_asteroid) <= collectable_size) {
			field.collect(closest_asteroid);
			collected_asteroids++;
			total_size += field.getSize(closest_asteroid);
		}
		else { cout << "The asteroid is too large to be collected." << endl; }
	}
	else { cout << "You are too far away from an asteroid." << endl; }
}

// Mutator, blasts an asteroid on the same coordinate as the spaceship
// @param: AsteroidList, to create new asteroids
void Spaceship::blastAsteroid(AsteroidList& field) {
	int closest_asteroid = searchField(field);
	int x, y;
	float size;
	double fraction = ((double)rand() / (RAND_MAX));
	// Generate a random number between 0 and 1

	// Check whether the spaceship and an asteroid are on the same coordinate
	if (getDistance(field, closest_asteroid) == 0) {

		// Generate a random coordinate and random size for the first fragment
		x = rand() % 100;
		y = rand() % 100;
		size = field.getSize(closest_asteroid) * fraction;

		// Create a new asteroid for the first fragment
		field.addAsteroid(x, y, size);

		// Check if the new asteroid hits the spaceship
		if (x == x_position && y == y_position) {
			cout << "An asteroid has hit the spaceship and damaged!" << endl;
			system("pause");
		}

		// Generate a random coordinate and random size for the second fragment
		x = rand() % 100;
		y = rand() % 100;
		size = field.getSize(closest_asteroid) - size;

		// Create another new asteroid for the second fragment
		field.addAsteroid(x, y, size);

		// Check if the new asteroid hits the spaceship
		if (x == x_position && y == y_position) {
			cout << "An asteroid has hit the spaceship and damaged!" << endl;
			system("pause");
		}

		// Remove the original asteroid by setting a flag on
		field.collect(closest_asteroid);

		// Although it is called "collect", the spaceship has not collected
		// The original asteroid, by not accumulating total_size and
		// not incrementing collected_asteroids.
	}
	else { cout << "You are too far away from an asteroid." << endl; }
}

// Accessor, searches a closest asteroid
// @param: AsteroidList, to search a closest asteroid
// @return: int
int Spaceship::searchField(const AsteroidList& field) const {

	// Largest possible distance within 100x100 grid is 142
	double min_distance = 142; 
	int index = -1;
	int x = 0;
	int y = 0;

	// Searches for minimum distance by linear search
	for (int i = 0; i < field.getLength(); i++) {

		// Skips the loop when an asteroid has already been collected
		if (!field.isCollected(i)) {

			// Skips the loop when an asteroid is far
			if (getDistance(field, i) < min_distance) {
				min_distance = getDistance(field, i);
				index = i;
			}
		}
	}
	return index;
}

// Accessor, gets a distance between a spaceship and given coordinates
// @param: 2 ints, x and y coordinates
// @return: double
double Spaceship::getDistance(int x, int y) const {
	double distance = sqrt(pow(x - x_position, 2) + pow(y - y_position, 2));
	return distance;
}

// Accessor, gets a distance between a spaceship and an asteroid
// @param: AsteroidList and int, to provide coordinates of an asteroid
// @return: double
double Spaceship::getDistance(const AsteroidList& field, int index) const {
	double distance;
	int x, y;

	// Obtains coordinates of an asteroid
	field.getCoordinates(x, y, index);
	distance = sqrt(pow(x - x_position, 2) + pow(y - y_position, 2));
	return distance;
}

// Accessor, gets a direction from a spaceship to an asteroid
// @param: AsteroidList and int, to provide coordinates of an asteroid
// @return: string
string Spaceship::getDirection(const AsteroidList& field, int index) const {
	string direction;
	double direction_in_degrees;
	int direction_in_zodiac;
	int x, y;

	// Obtains coordinates of an asteroid
	field.getCoordinates(x, y, index);
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

// Accessor, gets current coordinates of a spaceship
// @param: 2 ints, x and y coordinates
// @return: void (pass by reference)
void Spaceship::locate(int &x, int &y) const {
	x = x_position;
	y = y_position;
}

// Accessor, gets number of asteroids that a spaceship has collected
// @param: none
// @return: int
int Spaceship::getCollectedAsteroids() const { return collected_asteroids; }

// Accessor, gets collectable size of asteroids that a spaceship can collect
// @param: none
// @return: float
float Spaceship::getCollectableSize() const { return collectable_size; }

// Accessor, gets total size of asteroids that a spaceship has collected
// @param: none
// @return: float
float Spaceship::getTotalSize() const { return total_size; }

// Accessor, gets total distance that a spaceship has travelled
// @param: none
// @return: double
double Spaceship::getTotalDistance() const { return total_distance; }

/**
* This program allows a spaceship to collect asteroids efficiently.
* @version 1.0 2017-10-04
* @course CMPS2143 Dr. Stringfellow
* @author Yujin Yoshimura
*/

#include "asteroidlist.h"
#include "spaceship.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Imports values from an input file into an asteroid list.
void importFile(AsteroidList &field);

// Opens an input file.
ifstream openFile();

// Parse a line of string into two integers and one float values.
void parseValues(string line, int &x, int &y, float &s);

// Creates spaceship.
Spaceship createSpaceship();

// Let user choose whether to create a spaceship on a specific coordinates or not.
bool setCoordinates();

// Let user define the number of asteroids that a spaceship should collect.
int setQuota();

// Let user define the maximum size of asteroids that a spaceship can collect.
float setCollectableSize();

// Presentational function, displays the company name.
void displayCompanyHeader();

// Presentational function, displays the number of asteroids in the field.
void displayNumberOfAsteroids(const AsteroidList& field);

// Presentational function, displays the current location of the spaceship.
void displayCurrentLocation(const Spaceship& miner);

// Presentational function, displays the header for the list.
void displaysignalToEarthHeader();

// Presentational function, displays the coordinate and size of asteroid
// collected with distance travelled and direction of the spaceship.
void displaysignalToEarth(const Spaceship& miner, const AsteroidList& field, 
	bool blast, int closest_asteroid, int x, int y, double distance, string direction);

// Presentational function, displays the absence of asteroid
void displayAbsence();

// Presentational function, displays the total number of asteroids collected.
void displayCollectedAsteroids(const Spaceship& miner);

// Presentational function, displays the total size of the spaceship.
void displayTotalSize(const Spaceship& miner);

// Presentational function, displays the total distance of the spaceship.
void displayTotalDistance(const Spaceship& miner);

int main() {

	// Declare objects and variables
	int closest_asteroid, quota, x, y;
	double distance;
	string direction;
	bool blast;

	// Initialize asteroids
	AsteroidList asteroid_field;
	displayCompanyHeader();
	importFile(asteroid_field);
	displayNumberOfAsteroids(asteroid_field);

	// Initialize spaceship
	Spaceship asteroid_miner = createSpaceship();
	displayCurrentLocation(asteroid_miner);
	quota = setQuota();
	asteroid_miner.setSize(setCollectableSize());

	// Begin collection of asteroids
	displaysignalToEarthHeader();
	closest_asteroid = asteroid_miner.searchField(asteroid_field);
	while ((asteroid_miner.getCollectedAsteroids() < quota) && (closest_asteroid >= 0)) {
		asteroid_field.getCoordinates(x, y, closest_asteroid);
		distance = asteroid_miner.getDistance(asteroid_field, closest_asteroid);
		direction = asteroid_miner.getDirection(asteroid_field, closest_asteroid);
		asteroid_miner.move(x, y);

		// Collect asteroids, if possible
		if (asteroid_field.getSize(closest_asteroid) <= asteroid_miner.getCollectableSize()) {
			asteroid_miner.collectAsteroid(asteroid_field);
			blast = false;
		}

		// Otherwise, blast asteroids
		else {
			asteroid_miner.blastAsteroid(asteroid_field);
			blast = true;
		}
		displaysignalToEarth(asteroid_miner, asteroid_field, blast, closest_asteroid, x, y, distance, direction);
		closest_asteroid = asteroid_miner.searchField(asteroid_field);
	}
	displaysignalToEarthHeader();

	// Summarize
	if (closest_asteroid == -1) { displayAbsence(); }
	displayCollectedAsteroids(asteroid_miner);
	displayTotalSize(asteroid_miner);
	displayTotalDistance(asteroid_miner);

	system("pause");
	return 0;
}

// Imports values from an input file into an asteroid list.
// @param AsteroidList, where values will be stored into
void importFile(AsteroidList &field) {
	int x, y;
	float size;
	string line;

	ifstream myfile = openFile();
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			parseValues(line, x, y, size);
			field.addAsteroid(x, y, size);
		}
		myfile.close();
	}
	else { cout << "Unable to open file." << endl; }
}

// Opens an input file.
// @param: none
// @return: ifstream
ifstream openFile() {
	string file_name = "input.txt";
	ifstream myfile(file_name);
	return myfile;
}

// Parse a line of string into two integers and one float values.
// @param: string to be parsed, 2 int and 1 float that return parsed values
// @return: void (pass by reference)
void parseValues(string line, int &x, int &y, float &s) {
	stringstream stream(line);
	while (true) {
		stream >> x >> y >> s;
		if (!stream) { break; }
	}
}

// Creates spaceship.
// @param: none
// @return: Spaceship
Spaceship createSpaceship() {
	int x, y;
	if (setCoordinates()) {
		cout << "Please set x-coordinate of a spaceship: ";
		cin >> x;
		cout << "Please set y-coordinate of a spaceship: ";
		cin >> y;
		Spaceship miner(x, y);
		return miner;
	}
	else {
		Spaceship miner;
		return miner;
	}
}

// Let user choose whether to create a spaceship on a specific coordinates or not.
// @param: none
// @return: bool
bool setCoordinates() {
	char c;
	cout << "Do you want to set a spaceship on a specific coordinates? (Y/N): ";
	cin >> c;
	if (c == 'Y' || c == 'y') { return true; }
	else { return false; }
}

// Let user define the number of asteroids that a spaceship should collect.
// @param: none
// @return: int
int setQuota() {
	int quota;
	cout << "How many asteroids do you want a spaceship to collect?: ";
	cin >> quota;
	return quota;
}

// Let user define the maximum size of asteroids that a spaceship can collect.
// @param: none
// @return: float
float setCollectableSize() {
	float size;
	cout << "What is the maximum size of an asteroid that a spaceship can collect?: ";
	cin >> size;
	return size;
}

// Presentational function, displays the company name.
// @param: none
void displayCompanyHeader() {
	cout << "---------------------------------------------------------------" << endl
		<< "                      SPACE ASTEROID INC.                      " << endl
		<< "               Asteroid Mining Spaceship Program               " << endl
		<< "---------------------------------------------------------------" << endl;
}


// Presentational function, displays the number of asteroids in the field.
// @param: AsteroidList, to get number of asteroids
void displayNumberOfAsteroids(const AsteroidList& field) {
	cout << "There are " << field.getLength() << " asteroids in the field." << endl;
}

// Presentational function, displays the current location of the spaceship.
// @param: Spaceship, to get coordinates
void displayCurrentLocation(const Spaceship& miner) {
	int x, y;
	miner.locate(x, y);
	cout << "The spaceship has been originally located at: (" << x << ", " << y << ")" << endl;
}

// Presentational function, displays the header for the list.
// @param: none
void displaysignalToEarthHeader() {
	cout << "+-----+------------+------+---------------------+-------------+" << endl
		<< "| No. |  Position  | Size | Distance (in miles) |  Direction  |" << endl
		<< "+-----+------------+------+---------------------+-------------+" << endl;
}

// Presentational function, displays the coordinate and size of asteroid
// collected with distance travelled and direction of the spaceship.
// @param: Spaceship, AsteroidList, 3 int, double, string
void displaysignalToEarth(const Spaceship& miner, const AsteroidList& field, bool blast, int closest_asteroid, int x, int y, double distance, string direction) {
	string numberOfAsteroids;
	if (blast) { numberOfAsteroids = "N/A"; }
	else { numberOfAsteroids = to_string(miner.getCollectedAsteroids()); }

	cout << "| " << setw(3) << numberOfAsteroids << " | ("
		<< setw(3) << x << ", "
		<< setw(3) << y << ") | "
		<< setw(4) << fixed << setprecision(1) << field.getSize(closest_asteroid) << " | "
		<< setw(19) << fixed << setprecision(2) << distance * 10 << " | "
		<< setw(11) << direction << " |"
		<< endl;
}

// Presentational function, displays the absence of asteroid
// @param: none
void displayAbsence() {
	cout << "There are no more asteroids left." << endl
		<< "The spaceship has stopped collecting asteroids." << endl;
}

// Presentational function, displays the total number of asteroids collected.
// @param: Spaceship, to get total number of asteroids collected
void displayCollectedAsteroids(const Spaceship& miner) {
	cout << "The total number of asteroids that the spaceship has collected is: "
		<< miner.getCollectedAsteroids() << "." << endl;
}

// Presentational function, displays the total size of the spaceship.
// @param: Spaceship, to get total size of asteroids collected
void displayTotalSize(const Spaceship& miner) {
	cout << "The total size of asteroids that the spaceship has collected is: "
		<< miner.getTotalSize() << "." << endl;
}

// Presentational function, displays the total distance of the spaceship.
// @param: Spaceship, to get total distance travelled
void displayTotalDistance(const Spaceship& miner) {
	cout << "The total distance that the spaceship has travelled is: "
		<< miner.getTotalDistance() * 10 << " miles." << endl;
}

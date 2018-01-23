/**
* This program allows a spaceship to collect asteroids efficiently.
* @version 1.2 2017-10-23
* @course CMPS2143 Dr. Stringfellow
* @author Yujin Yoshimura
*/

#include "asteroidlist.h"
#include "spaceprobe.h"
#include "spaceship.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const int DIMENSION = 100;

// Imports values from an input file into an asteroid list.
void importFile(AsteroidList &field);

// Opens an input file.
ifstream openFile();

// Parse a line of string into two integers and one float values.
void parseValues(string line, int &x, int &y, float &s, char &m);

// Creates spaceprobe.
SpaceProbe createSpaceProbe(string &spacecraft);

// Creates spaceship.
Spaceship createSpaceship(string &spacecraft);

// Let user choose whether to create a spacecraft on a specific coordinates.
bool isParameterizedCoordinates(string spacecraft);

// Prevents users to input values other than integer.
int inputInt();

// Let user enter the actual values for the coordinates, then validate.
int inputCoordinate(char variable);

// Sets the coordinates of a spacecraft to user defined coordinates.
void setCoordinates(int &x, int &y);

// Let user define the number of asteroids that a spaceship should collect.
int setQuota();

// Let user define the maximum size of asteroids that a spaceship can collect.
float setCollectableSize();

// Presentational function, displays the company name.
void displayCompanyHeader();

// Presentational function, displays the number of asteroids in the field.
void displayNumberOfAsteroids(const AsteroidList& field);

// Presentational function, displays the current location of the spacecraft.
void displayCurrentLocation(int x, int y, string spacecraft);

// Presentational function, displays initiation of space probe's signal.
void displaySpaceProbeInitiation();

// Presentational function, displays initiation of spaceship's signal.
void displaySpaceshipInitiation();

// Presentational function, displays the header for the list.
void displaysignalToEarthHeader();

// Presentational function, displays the coordinate and size of asteroid
// visited with distance travelled and direction of the spacecraft.
void displaysignalToEarth(const AsteroidList& field, int closest,
	string number, string status, double distance, string direction);

// Presentational function, tell by string the number of asteroids prospected.
string number(const SpaceProbe& probe);

// Presentational function, tell by string the number of asteroids collected.
// If the asteroid has been blasted, it returns "N/A".
string number(const Spaceship& ship, bool blast);

// Presentational function, tell by string whether the asteroid contains
// precious metal or not.
string metal(const AsteroidList& field, int closest);

// Presentational function, tell by string whether the asteroid has been
// collected or blasted by the spaceship.
string status(bool blast);

// Presentational function, displays the number of asteroids with precious metals.
void displayPreciousAsteroids(const AsteroidList& field);

// Presentational function, displays the absence of asteroid.
void displayAbsence();

// Presentational function, displays the total number of asteroids collected.
void displayCollectedAsteroids(int collected_asteroids);

// Presentational function, displays the total size of the spaceship.
void displayTotalSize(float total_size);

// Presentational function, displays the total distance of the spacecraft.
void displayTotalDistance(double total_distance, string spacecraft);

int main() {

	// Declare objects and variables
	int closest, quota, x, y;
	double distance;
	string direction, type;
	bool blast;

	// Initialize asteroids
	AsteroidList field;
	displayCompanyHeader();
	importFile(field);
	displayNumberOfAsteroids(field);

	// Initialize spaceprobe
	SpaceProbe probe = createSpaceProbe(type);
	probe.getCoordinates(x, y);
	displayCurrentLocation(x, y, type);

	// SpaceProbe begins prospection of asteroids
	displaySpaceProbeInitiation();
	displaysignalToEarthHeader();
	closest = probe.searchField(field);
	while (closest >= 0) {
		field.getAsteroid(closest).getCoordinates(x, y);
		distance = probe.getDistance(field, closest);
		direction = probe.getDirection(field, closest);
		probe.move(x, y);
		probe.prospectAsteroid(field);
		displaysignalToEarth(field, closest, number(probe), metal(field, closest),
			distance, direction);
		closest = probe.searchField(field);
	}
	displaysignalToEarthHeader();
	AsteroidList precious_list(probe.getPreciousAsteroidList());
	displayPreciousAsteroids(precious_list);
	displayTotalDistance(probe.getTotalDistance(), type);

	// Initialize spaceship
	Spaceship ship = createSpaceship(type);
	ship.getCoordinates(x, y);
	displayCurrentLocation(x, y, type);
	quota = setQuota();
	ship.setSize(setCollectableSize());

	// Spaceship begins collection of asteroids
	displaySpaceshipInitiation();
	displaysignalToEarthHeader();
	closest = ship.searchField(precious_list);
	while ((ship.getVisitedAsteroids() < quota) && (closest >= 0)) {
		precious_list.getAsteroid(closest).getCoordinates(x, y);
		distance = ship.getDistance(precious_list, closest);
		direction = ship.getDirection(precious_list, closest);
		ship.move(x, y);

		// Collect asteroids, if possible
		if (precious_list.getAsteroid(closest).getSize() <= ship.getCollectableSize()) {
			ship.collectAsteroid(precious_list);
			blast = false;
		}

		// Otherwise, blast asteroids
		else {
			ship.blastAsteroid(precious_list);
			blast = true;
		}
		displaysignalToEarth(precious_list, closest, number(ship, blast), 
			status(blast), distance, direction);
		closest = ship.searchField(precious_list);
	}
	displaysignalToEarthHeader();

	// Summarize
	if (closest == -1) { displayAbsence(); }
	displayCollectedAsteroids(ship.getVisitedAsteroids());
	displayTotalSize(ship.getTotalSize());
	displayTotalDistance(ship.getTotalDistance(), type);

	system("pause");
	return 0;
}

// Imports values from an input file into an asteroid list.
// @param AsteroidList, where values will be stored into
void importFile(AsteroidList &field) {
	int x, y;
	float size;
	char metal;
	string line;

	ifstream myfile = openFile();
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			parseValues(line, x, y, size, metal);
			field.addAsteroid(x, y, size, metal);
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
void parseValues(string line, int &x, int &y, float &s, char &m) {
	stringstream stream(line);
	while (true) {
		stream >> x >> y >> s >> m;
		if (!stream) { break; }
	}
}

// Creates space probe.
// @param: string to return the type of spacecraft, pass by reference
// @return: SpaceProbe
SpaceProbe createSpaceProbe(string &spacecraft) {
	int x, y;
	spacecraft = "space probe";
	cout << endl << "Preparing for space probe..." << endl;
	if (isParameterizedCoordinates("space probe")) {
		setCoordinates(x, y);
		SpaceProbe explorer(x, y);
		return explorer;
	}
	else {
		SpaceProbe explorer;
		return explorer;
	}
}

// Creates spaceship.
// @param: string to return the type of spacecraft, pass by reference
// @return: Spaceship
Spaceship createSpaceship(string &spacecraft) {
	int x, y;
	spacecraft = "spaceship";
	cout << endl << "Preparing for spaceship..." << endl;
	if (isParameterizedCoordinates("spaceship")) {
		setCoordinates(x, y);
		Spaceship miner(x, y);
		return miner;
	}
	else {
		Spaceship miner;
		return miner;
	}
}

// Let user choose whether to create a spacecraft on a specific coordinates.
// @param: none
// @return: bool
bool isParameterizedCoordinates(string spacecraft) {
	char c;
	bool valid = false;
		cout << "Do you want to set a " << spacecraft << " on a specific coordinates? (Y/N): ";
	while (!valid) {
		cin >> c;
		if (c == 'Y' || c == 'y') {
			valid = true;
			return true;
		}
		else if (c == 'N' || c == 'n') { 
			valid = true; 
			return false;
		}
		else { 
			cout << "the character you entered is invalid. Please enter again : ";
		}
	}
}

// Prevents users to input values other than integer.
// @param: none
// @return: int
int inputInt() {
	int input;

	cin >> input;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "the value you entered is invalid. Please enter again : ";
		cin >> input;
	}
	return input;
}

// Let user enter the actual values for the coordinates, then validate.
// @param: char, to define either x-coordinate or y-coordinate
// @return: int
int inputCoordinate(char variable) {
	bool valid = false;
	int input;

	while (!valid) {
		cout << "Please set " << variable << "-coordinate of a spaceship: ";
		input = inputInt();
		if (input >= 0 && input <= DIMENSION) { valid = true; }
		else { cout << "the value you entered is invalid. Please enter again : "; }
	}
	return input;
}

// Sets the coordinates of a spacecraft to user defined coordinates.
// @param: 2 int to set coordinates
// @return: void (pass by reference)
void setCoordinates(int &x, int &y) {
	x = inputCoordinate('x');
	y = inputCoordinate('y');
}

// Let user define the number of asteroids that a spaceship should collect.
// @param: none
// @return: int
int setQuota() {
	int quota;
	cout << "How many asteroids do you want a spaceship to collect?: ";
	quota = inputInt();
	return quota;
}

// Let user define the maximum size of asteroids that a spaceship can collect.
// @param: none
// @return: float
float setCollectableSize() {
	float size;
	cout << "What is the maximum size of an asteroid that a spaceship can collect?: ";
	size = inputInt();
	return size;
}

// Presentational function, displays the company name.
// @param: none
void displayCompanyHeader() {
	cout << "---------------------------------------------------------------------------" << endl
		<< "                            SPACE ASTEROID INC.                            " << endl
		<< "                     Asteroid Mining Spaceship Program                     " << endl
		<< "---------------------------------------------------------------------------" << endl;
}


// Presentational function, displays the number of asteroids in the field.
// @param: AsteroidList, to get number of asteroids
void displayNumberOfAsteroids(const AsteroidList& field) {
	cout << "There are " << field.getLength() << " asteroids in the field." << endl;
}

// Presentational function, displays the current location of the spacecraft.
// @param: 2 ints for coordinates, and string to determine type of spacecraft.
void displayCurrentLocation(int x, int y, string spacecraft) {
	cout << "The " << spacecraft << " has been originally located at: (" << x << ", " << y << ")" << endl;
}

// Presentational function, displays initiation of space probe's signal.
// @param: none
void displaySpaceProbeInitiation() {
	cout << endl << "Space probe begins to prospect asteroids." << endl;
}

// Presentational function, displays initiation of spaceship's signal.
// @param: none
void displaySpaceshipInitiation() {
	cout << endl << "Spaceship begins to collect asteroids with precious metals." << endl;
}

// Presentational function, displays the header for the list.
// @param: none
void displaysignalToEarthHeader() {
	cout << "+-----+------------+------+------------+---------------------+-------------+" << endl
		<< "| No. |  Position  | Size |   Status   | Distance (in miles) |  Direction  |" << endl
		<< "+-----+------------+------+------------+---------------------+-------------+" << endl;
}

// Presentational function, displays the coordinate and size of asteroid
// visited with distance travelled and direction of the spacecraft.
// @param: AsteroidList, int, double, 2 strings
void displaysignalToEarth(const AsteroidList& field, int closest, string number,
	string status, double distance, string direction) {
	cout << "| " << setw(3) << right << number << " | ("
		<< setw(3) << right << field.getAsteroid(closest).getX() << ", "
		<< setw(3) << right << field.getAsteroid(closest).getY() << ") | "
		<< setw(4) << right << fixed << setprecision(1) << field.getAsteroid(closest).getSize() << " | "
		<< setw(10) << left << status << " | "
		<< setw(19) << right << fixed << setprecision(2) << distance * 10 << " | "
		<< setw(11) << left << direction << " |"
		<< endl;
}

// Presentational function, tell by string the number of asteroids prospected.
// @param: SpaceProbe
// @return: string
string number(const SpaceProbe& probe) {
	string numberOfAsteroids = to_string(probe.getVisitedAsteroids());
	return numberOfAsteroids;
}

// Presentational function, tell by string the number of asteroids collected.
// If the asteroid has been blasted, it returns "N/A".
// @param: Spaceship and bool to tell whether it has been blasted or not
// @return: string
string number(const Spaceship& ship, bool blast) {
	string numberOfAsteroids;
	if (blast) { numberOfAsteroids = "N/A"; }
	else { numberOfAsteroids = to_string(ship.getVisitedAsteroids()); }
	return numberOfAsteroids;
}

// Presentational function, tell by string whether the asteroid contains
// precious metal or not.
// @param: AsteroidList and int that tells which asteroid has been prospected
// @return: string
string metal(const AsteroidList& field, int closest) {
	string metal;
	if (field.getAsteroid(closest).isPrecious()) { metal = "Precious"; }
	else { metal = "Not"; }
	return metal;
}

// Presentational function, tell by string whether the asteroid has been
// collected or blasted by the spaceship.
// @param: bool to tell whether it has been blasted or not
// @return: string
string status(bool blast) {
	string status;
	if (blast) { status = "Blasted"; }
	else { status = "Collected"; }
	return status;
}

// Presentational function, displays the number of asteroids with precious metals.
// @param: none
void displayPreciousAsteroids(const AsteroidList& field) {
	cout << "The total number of asteroids that contains precious metal is: "
		<< setw(12) << right << field.getLength() << endl;
}

// Presentational function, displays the absence of asteroid.
// @param: none
void displayAbsence() {
	cout << "There are no more asteroids left." << endl
		<< "The spaceship has stopped collecting asteroids." << endl;
}

// Presentational function, displays the total number of asteroids collected.
// @param: int, that tells the total number of asteroids collected
void displayCollectedAsteroids(int collected_asteroids) {
	cout << "The total number of asteroids that the spaceship has collected is: "
		<< setw(8) << right << collected_asteroids << endl;
}

// Presentational function, displays the total size of the spaceship.
// @param: float, that tells the total size of the spaceship
void displayTotalSize(float total_size) {
	cout << "The total size of asteroids that the spaceship has collected is: "
		<< setw(10) << right << total_size << endl;
}

// Presentational function, displays the total distance of the spacecraft.
// @param: double, that tells the total distance of the spacecraft.
void displayTotalDistance(double total_distance, string spacecraft) {
	int width = 12;
	if (spacecraft == "space probe") { width = 11; }
	else if (spacecraft == "spaceship") { width = 13; }

	cout << "The total distance that the " << spacecraft << " has travelled is: "
		<< setw(width) << right << total_distance * 10 << " miles" << endl;
}
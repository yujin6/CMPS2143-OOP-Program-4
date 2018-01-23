/**
* This program allows a fleet of spacecrafts to collect asteroids efficiently.
* @version 1.3 2017-11-13
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
using namespace std;

typedef Spacecraft** SpaceFleet;

// Opens an input file.
ifstream openFile(string filename);

// Parse a line of string into two integers, one float and one char values.
void parseAsteroid(string line, int &x, int &y, float &s, char &m);

// Parse a line of string into one char and two integer values.
void parseSpacecraft(string line, char &t, int &x, int &y);

// Imports Asteroid data from an input file into an asteroid list.
void importAsteroid(AsteroidList &field);

// Imports Space Fleet data from an input file into an array of string.
int importSpaceFleet(string lines[]);

// Creates a fleet of Spacecrafts.
SpaceFleet createSpaceFleet(int &num_spacecrafts);

// Presentational function, displays the company name.
void displayCompanyHeader();

// Presentational function, displays each spacecrafts' status in space fleet.
void displayStatusReport(SpaceFleet fleet, int num_spacecrafts);

// Presentational function, displays the number of asteroids in the field.
void displayNumberOfAsteroids(const AsteroidList& field);

// Presentational function, displays initiation of space probe's signal.
void displaySpaceProbeInitiation();

// Presentational function, displays initiation of spaceship's signal.
void displaySpaceshipInitiation();

// Presentational function, displays the header for the list.
void displaysignalToEarthHeader();

// Presentational function, displays the coordinate and size of asteroid
// visited with distance travelled and direction of the spacecraft.
void displaysignalToEarth(const Spacecraft& craft, const AsteroidList& field,
	int closest, bool blast, double distance, string direction);

// Presentational function, tell by string the number of asteroids visited.
// If the asteroid has been blasted, it returns "N/A".
string number(const Spacecraft& craft, bool blast);

// Presentational function, tell by string the asteroid's data.
// For space probes, the status shows precious or not.
// For spaceship, the status shows collected or blasted.
string asteroidStatus(const Spacecraft& craft, const AsteroidList& field,
	int closest, bool blast);

// Presentational function, tell by string whether the asteroid has been
// collected or blasted by the spaceship.
string status(bool blast);

// Presentational function, displays the number of asteroids with precious metals.
void displayPreciousAsteroids(const AsteroidList& field);

// Presentational function, displays the absence of asteroid.
void displayAbsence();

// Presentational function, displays the summary of 4 static variables.
void displaySummary();

/*
	// Creates spaceprobe.
	SpaceProbe createSpaceProbe(string &spacecraft);

	// Creates spaceship.
	Spaceship createSpaceship(string &spacecraft);

	// Let user choose whether to create a spacecraft on a specific coordinates.
	bool isParameterizedCoordinates(string spacecraft);

	// Prevents users to input values other than integer.
	int inputInt();

	// Let user enter the actual values for the coordinates, then validate.
	int inputCoordinate(char variable, string spacecraft);

	// Sets the coordinates of a spacecraft to user defined coordinates.
	void setCoordinates(int &x, int &y, string spacecraft);

	// Let user define the number of asteroids that a spaceship should collect.
	int setQuota();

	// Let user define the maximum size of asteroids that a spaceship can collect.
	float setCollectableSize();

	// Presentational function, displays the current location of the spacecraft.
	void displayCurrentLocation(int x, int y, string spacecraft);

	// Presentational function, tell by string whether the asteroid contains
	// precious metal or not.
	string metal(const AsteroidList& field, int closest);

	// Presentational function, displays the total number of asteroids collected.
	void displayCollectedAsteroids(int collected_asteroids);

	// Presentational function, displays the total size of the spaceship.
	void displayTotalSize(float total_size);

	// Presentational function, displays the total distance of the spacecraft.
	void displayTotalDistance(double total_distance, string spacecraft);
*/

int main() {

	// Declare variables
	int num_spacecrafts, closest, x, y, i;
	double distance;
	string direction;
	bool blast;

	// Initialize space fleet
	SpaceFleet fleet = createSpaceFleet(num_spacecrafts);
	displayCompanyHeader();
	displayStatusReport(fleet, num_spacecrafts);

	// Initialize asteroids
	AsteroidList field;
	importAsteroid(field);
	displayNumberOfAsteroids(field);

	// Space probe begins prospection of asteroids
	displaySpaceProbeInitiation();
	displaysignalToEarthHeader();
	i = 0;
	closest = fleet[i]->searchField(field);
	while ((Spacecraft::getProspected() < Spacecraft::getMaxProspect()) 
		&& (closest >= 0)) {
		if (fleet[i]->getType() == 'P') {
			SpaceProbe* probe = (SpaceProbe*)(fleet[i]);
			field.getAsteroid(closest).getCoordinates(x, y);
			distance = probe->getDistance(field, closest);
			direction = probe->getDirection(field, closest);
			probe->move(x, y);
			*probe + field;
			displaysignalToEarth(*probe, field, closest, false, distance, direction);
		}
		(i < num_spacecrafts - 1) ? i++ : i = 0;
		closest = fleet[i]->searchField(field);
	}
	displaysignalToEarthHeader();

	// Summarize space probe
	AsteroidList plist = fleet[i]->getPreciousAsteroidList();
	displayPreciousAsteroids(plist);

	// Spaceship begins collection of asteroids
	displaySpaceshipInitiation();
	displaysignalToEarthHeader();
	i = 0;
	closest = fleet[i]->searchField(plist);
	while ((Spacecraft::getCollected() < Spacecraft::getMaxCollect())
		&& (closest >= 0)) {
		if (fleet[i]->getType() == 'S') {
			Spaceship* ship = (Spaceship*)(fleet[i]);
			plist.getAsteroid(closest).getCoordinates(x, y);
			distance = ship->getDistance(plist, closest);
			direction = ship->getDirection(plist, closest);
			ship->move(x, y);

			// Collect asteroids, if possible
			if (plist.getAsteroid(closest).getSize() <= ship->getSize()) {
				*ship + plist;
				blast = false;
				displaysignalToEarth(*ship, plist, closest, blast, distance, direction);
			}

			// Otherwise, blast asteroids
			else {
				*ship * plist;
				blast = true;
				displaysignalToEarth(*ship, plist, closest, blast, distance, direction);
				for (int j = 0; j < num_spacecrafts; j++) {
					fleet[j]->checkDamage(plist, closest);
				}
			}
		}
		(i < num_spacecrafts - 1) ? i++ : i = 0;
		closest = fleet[i]->searchField(plist);
	}
	displaysignalToEarthHeader();

	// Summarize spaceship
	if (closest == -1) { displayAbsence(); }
	displayStatusReport(fleet, num_spacecrafts);
	displaySummary();
	system("pause");
	return 0;
}

// Opens an input file.
// @param: none
// @return: ifstream
ifstream openFile(string filename) {
	string file_name = filename;
	ifstream myfile(file_name);
	return myfile;
}

// Parse a line of string into two integers, one float and one char values.
// @param: string to be parsed, 2 int, 1 float, 1 char, that return parsed values
// @return: void (pass by reference)
void parseAsteroid(string line, int &x, int &y, float &s, char &m) {
	stringstream stream(line);
	while (true) {
		stream >> x >> y >> s >> m;
		if (!stream) { break; }
	}
}

// Parse a line of string into one char and two integer values.
// @param: string to be parsed, 1 char, 2 int, that return parsed values
// @return: void (pass by reference)
void parseSpacecraft(string line, char &t, int &x, int &y) {
	stringstream stream(line);
	while (true) {
		stream >> t >> x >> y;
		if (!stream) { break; }
	}
}

// Imports Asteroid data from an input file into an asteroid list.
// @param AsteroidList, where Asteroid data will be stored into
void importAsteroid(AsteroidList &field) {
	int x, y;
	float size;
	char metal;
	string line;

	ifstream myfile = openFile("input.txt");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			parseAsteroid(line, x, y, size, metal);
			Asteroid temp(x, y, size, metal);
			field += temp;
		}
		myfile.close();
	}
	else { cout << "Unable to open file." << endl; }
}

// Imports Space Fleet data from an input file into an array of string.
// @param  array of string, where Space Fleet data will be stored into
// @return: int
int importSpaceFleet(string lines[]) {
	int length = 0;
	string line;

	ifstream myfile = openFile("Spacecraft.txt");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			lines[length] = line;
			length++;
		}
		myfile.close();
	}
	else { cout << "Unable to open file." << endl; }

	return length;
}

// Creates a fleet of Spacecrafts.
// @param: 2 ints (pass by reference)
// @return: array of pointers to Spacecraft
SpaceFleet createSpaceFleet(int &num_spacecrafts) {
	string lines[255];
	int length = 0, j = 1, k = 1;
	string name;
	int x, y;
	char type;
	Spacecraft** fleet;

	length = importSpaceFleet(lines);
	if (length > 4) {
		num_spacecrafts = stoi(lines[0]);
		Spacecraft::setMaxProspect(stoi(lines[1]));
		Spacecraft::setMaxCollect(stoi(lines[2]));

		fleet = new Spacecraft*[num_spacecrafts];
		for (int i = 0; i < num_spacecrafts; i++) {
			parseSpacecraft(lines[i+4], type, x, y);
			if (type == 'P' || type == 'p') {
				name = "Probe " + to_string(j);
				fleet[i] = new SpaceProbe(name, x, y);
				j++;
			}
			else if (type == 'S' || type == 's') {
				name = "Ship " + to_string(k);
				fleet[i] = new Spaceship(name, x, y);
				Spaceship* ship = (Spaceship*)(fleet[i]);
				ship->setSize(stof(lines[3]));
				k++;
			}
		}
	}
	return fleet;
}

// Presentational function, displays the company name.
// @param: none
void displayCompanyHeader() {
	cout << "---------------------------------------------------------------------------" << endl;
	cout << "                            SPACE ASTEROID INC.                            " << endl;
	cout << "                     Asteroid Mining Spaceship Program                     " << endl;
	cout << "---------------------------------------------------------------------------" << endl;
}

// Presentational function, displays each spacecrafts' status in space fleet.
// @param: SpaceFleet, int to tell number of spacecrafts in the space fleet
void displayStatusReport(SpaceFleet fleet, int num_spacecrafts) {
	string header = "";
	header += "+--------------+----------+------------+---------+----------------+-------+\n";
	header += "|     Type     |   Name   |  Position  | Visited | Total Distance | Cargo |\n";
	header += "+--------------+----------+------------+---------+----------------+-------+\n";

	cout << endl << "Space Fleet Status Report :" << endl;
	cout << header;
	for (int i = 0; i < num_spacecrafts; i++) {
		cout << fleet[i]->toString() << endl;
	}
	cout << header;
}

// Presentational function, displays the number of asteroids in the field.
// @param: AsteroidList, to get number of asteroids
void displayNumberOfAsteroids(const AsteroidList& field) {
	string number = field.toString();
	string delimiter = "\n";
	string token = number.substr(0, number.find(delimiter));
	cout << token << endl; // truncates the AsteroidList toString method
}

// Presentational function, displays initiation of space probe's signal.
// @param: none
void displaySpaceProbeInitiation() {
	cout << endl << "Space probes begin to prospect up to ";
	cout << Spacecraft::getMaxProspect() << " asteroids." << endl;
}

// Presentational function, displays initiation of spaceship's signal.
// @param: none
void displaySpaceshipInitiation() {
	cout << endl << "Spaceships begin to collect up to ";
	cout << Spacecraft::getMaxCollect() << " asteroids with precious metals." << endl;
}

// Presentational function, displays the header for the list.
// @param: none
void displaysignalToEarthHeader() {
	string header = "";
	header += "+-----+------------+------+------------+----------+----------+-------------+\n";
	header += "| No. |  Position  | Size |   Status   |   Name   | Distance |  Direction  |\n";
	header += "+-----+------------+------+------------+----------+----------+-------------+\n";
	cout << header;
}

// Presentational function, displays the coordinate and size of asteroid
// visited with distance travelled and direction of the spacecraft.
// @param: AsteroidList, int, double, 2 strings
void displaysignalToEarth(const Spacecraft& craft, const AsteroidList& field, int closest,
	bool blast, double distance, string direction) {
	cout << "| " << setw(3) << right << number(craft, blast) << " "
		<< asteroidStatus(craft, field, closest, blast)
		<< setw(8) << left << craft.getName() << " | "
		<< setw(8) << right << fixed << setprecision(2) << distance * 10 << " | "
		<< setw(11) << left << direction << " |"
		<< endl;
}

// Presentational function, tell by string the number of asteroids visited.
// If the asteroid has been blasted, it returns "N/A".
// @param: Spacecraft and bool to tell whether it has been blasted or not
// @return: string
string number(const Spacecraft& craft, bool blast) {
	string numberOfAsteroids;
	if (craft.getType() == 'P') {
		numberOfAsteroids = to_string(Spacecraft::getProspected());
	}
	else {
		if (blast) { numberOfAsteroids = "N/A"; }
		else { numberOfAsteroids = to_string(Spacecraft::getCollected()); }
	}
	return numberOfAsteroids;
}

// Presentational function, tell by string the asteroid's data.
// For space probes, the status shows precious or not.
// For spaceship, the status shows collected or blasted.
// @param: Spacecraft, AsteroidList, int and bool
// @return: string
string asteroidStatus(const Spacecraft& craft, const AsteroidList& field,
	int closest, bool blast) {
	string s = field.getAsteroid(closest).toString();
	stringstream stream("");
	int width;

	(craft.getType() == 'P') ? width = 35 : width = 22;
	s.resize(width); // truncates the Asteroid toString method
	stream << s;
	if (craft.getType() == 'S') {
		stream << setw(10) << left << status(blast) << " | ";
	}
	return stream.str();
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
// @param: AsteroidList
void displayPreciousAsteroids(const AsteroidList& field) {
	cout << endl << "Space probes' combined visited precious metals asteroid list: " << endl;
	cout << Spacecraft::getList();
}

// Presentational function, displays the absence of asteroid.
// @param: none
void displayAbsence() {
	cout << "There are no more asteroids left." << endl;
	cout << "The spaceship has stopped collecting asteroids." << endl;
}

// Presentational function, displays the summary of 4 static variables.
// @param: none
void displaySummary() {
	cout << endl << "Summary : " << endl;
	cout << "Total number of asteroids to visit by space probes : ";
	cout << setw(21) << right << Spacecraft::getMaxProspect() << endl;
	cout << "Total number of asteroids visited by space probes : ";
	cout << setw(22) << right << Spacecraft::getProspected() << endl;
	cout << "Total number of asteroids to collect by spaceships : ";
	cout << setw(21) << right << Spacecraft::getMaxCollect() << endl;
	cout << "Total number of asteroids collected by spaceships : ";
	cout << setw(22) << right << Spacecraft::getCollected() << endl;
}

/*
	// Creates space probe.
	// @param: string to return the type of spacecraft, pass by reference
	// @return: SpaceProbe
	SpaceProbe createSpaceProbe(string &spacecraft) {
		int x, y;
		spacecraft = "space probe";
		cout << endl << "Preparing for space probe..." << endl;
		if (isParameterizedCoordinates("space probe")) {
			setCoordinates(x, y, spacecraft);
			SpaceProbe probe(x, y);
			return probe;
		}
		else {
			SpaceProbe probe;
			return probe;
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
			setCoordinates(x, y, spacecraft);
			Spaceship ship(x, y);
			return ship;
		}
		else {
			Spaceship ship;
			return ship;
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
	int inputCoordinate(char variable, string spacecraft) {
		bool valid = false;
		int input;

		while (!valid) {
			cout << "Please set " << variable << "-coordinate of a " << spacecraft << " : ";
			input = inputInt();
			if (input >= 0 && input <= SpaceObject::DIMENSION) { valid = true; }
			else { cout << "the value you entered is invalid. Please enter again : "; }
		}
		return input;
	}

	// Sets the coordinates of a spacecraft to user defined coordinates.
	// @param: 2 int to set coordinates
	// @return: void (pass by reference)
	void setCoordinates(int &x, int &y, string spacecraft) {
		x = inputCoordinate('x', spacecraft);
		y = inputCoordinate('y', spacecraft);
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
		size = (float) inputInt();
		return size;
	}

	// Presentational function, displays the current location of the spacecraft.
	// @param: 2 ints for coordinates, and string to determine type of spacecraft.
	void displayCurrentLocation(int x, int y, string spacecraft) {
		cout << "The " << spacecraft << " has been originally located at: (";
		cout << x << ", " << y << ")" << endl;
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

	// Presentational function, displays the total number of asteroids collected.
	// @param: int, that tells the total number of asteroids collected
	void displayCollectedAsteroids(int collected_asteroids) {
		cout << "The total number of asteroids that the spaceships have collected is: ";
		cout << setw(6) << right << collected_asteroids << endl;
	}

	// Presentational function, displays the total size of the spaceship.
	// @param: float, that tells the total size of the spaceship
	void displayTotalSize(float total_size) {
		cout << "The total size of asteroids that the spaceship has collected is: ";
		cout << setw(10) << right << total_size << endl;
	}

	// Presentational function, displays the total distance of the spacecraft.
	// @param: double, that tells the total distance of the spacecraft.
	void displayTotalDistance(double total_distance, string spacecraft) {
		cout << "The total distance that the " << spacecraft << " has travelled is: ";
		cout << setw(22 - spacecraft.length()) << right << total_distance * 10;
		cout << " miles" << endl;
	}
*/

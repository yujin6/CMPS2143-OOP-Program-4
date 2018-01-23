#pragma once
#include <string>
using namespace std;

class SpaceObject {
public:

	// Determines the dimension of the coordinates where space object can be placed.
	static const int DIMENSION = 100;

	// Default Constructor
	SpaceObject();

	// Copy Constructor
	SpaceObject(const SpaceObject &other);

	// Parameterized Constructor with user defined coordinates
	SpaceObject(int x, int y);

	// Destructor
	~SpaceObject();

	// Mutator, sets a space object with user defined coordinates
	void setCoordinates(int x, int y);

	// Accessor, gets both coordinates of a space object
	void getCoordinates(int &x, int &y);

	// Accessor, gets x-coordinate of a space object
	int getX() const;

	// Accessor, gets y-coordinate of a space object
	int getY() const;

	// Accessor, gets a name of space object
	string getName() const;

	// Accessor, tells formatted space object data by string
	virtual string toString() const;

protected:

	int x; // Determines x-coordinate of a space object
	int y; // Determines y-coordinate of a space object
	string name; // Name of a space object

private:

	// Prevents user defined coordinates to be outside of the region
	// Such that both x and y must be between 0 and 100
	int validate(int z);

};

#pragma once
using namespace std;

class SpaceObject {
public:

	// Determines the dimension of the coordinates where space object can be placed.
	const int DIMENSION = 100;

/* Since SpaceObject class is an abstract class, its instance should never be made.
Constructors and destructor are unnecessary.

	// Default Constructor
	SpaceObject();

	// Copy Constructor
	SpaceObject(const SpaceObject &other);

	// Parameterized Constructor with user defined coordinates
	SpaceObject(int x, int y);

	// Destructor
	~SpaceObject();

*/

	// Mutator, sets a space object with user defined coordinates
	void setCoordinates(int x, int y);

	// Accessor, gets both coordinates of a space object
	void getCoordinates(int &x, int &y);

	// Accessor, gets x-coordinate of a space object
	int getX() const;

	// Accessor, gets y-coordinate of a space object
	int getY() const;

protected:

	// Prevents user defined coordinates to be outside of the region
	// Such that both x and y must be between 0 and 100
	int validate(int z);

	int x_position; // Determines x-coordinate of a space object
	int y_position; // Determines y-coordinate of a space object

};
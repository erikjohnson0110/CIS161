//Header file for my Camper class.  This contains the class definition, and function prototypes for my Camper class
// The Camper class represents a camper within the program.
#ifndef CAMPER_H
#define CAMPER_H

#include <string>

using namespace std;

// Camper class definition
class Camper 
{
	// private members
private:
	string name;  // string to hold camper name
	bool paid;    // bool to store if the camper has paid

	// public members
public:
	// default constructor
	Camper() 
	{
		name = "A Happy Camper"; // set name to default
		paid = false;            // set paid status to false
	}

	// non-default constructor that accepts one string argument.
	Camper(string n) 
	{
		name = n;      // set name to the string parameter
		paid = false;  // set paid to false
	}

	// destructor
	~Camper() {
	}

	// Function Prototypes
	string getName(); // accessor - returns name property
	void pay();       // helper - sets camper paid status to true
	bool hasPaid();   // accessor - returns the value of paid
	string display(); // helper - returns a string that contains all of the object's property values (name, paid status)
};

#endif // !CAMPER_H


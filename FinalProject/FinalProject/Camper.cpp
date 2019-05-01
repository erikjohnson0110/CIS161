// Function definitions for the Camper class
#include "Camper.h"

// getName returns the value of the object's "name" property
string Camper::getName() {
	return name;
}

// pay sets the value of the object's "paid" property to true.
// Upon instantiation, all Campers paid status is defaulted to false.
void Camper::pay() {
	if (!hasPaid()) // if the camper has not paid
	{
		paid = true;// set paid to true
	}
}

// hasPaid returns the boolean value of the object's "paid" property
bool Camper::hasPaid() {
	return paid; 
}

// display returns a string that contains the object's property values formatted as:
// [Camper - Name: %n, Has Paid: %p(yes/no)]
// ex:  [Camper - Name: Erik, Has Paid: Yes]
string Camper::display() {
	string returnMessage = "[Camper - Name: " + name + ", " + "Has Paid: "; // assign the first portion of the string
	if (hasPaid())
	{
		returnMessage += "Yes]";  // if paid, concatenate "Yes"
	}
	else 
	{
		returnMessage += "No]";  // if not paid, concatenate "No"
	}
	return returnMessage;        // return the string
}
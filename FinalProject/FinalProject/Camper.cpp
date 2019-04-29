#include "Camper.h"

string Camper::getName() {
	return name;
}

void Camper::pay() {
	if (!hasPaid()) 
	{
		paid = true;
	}
	else 
	{
		// throw already paid exception?
	}
}

bool Camper::hasPaid() {
	return paid;
}

string Camper::display() {
	string returnMessage = "[Camper - Name: " + name + ", " + "Has Paid: ";
	if (hasPaid())
	{
		returnMessage += "Yes]";
	}
	else 
	{
		returnMessage += "No]";
	}
	return returnMessage;
}
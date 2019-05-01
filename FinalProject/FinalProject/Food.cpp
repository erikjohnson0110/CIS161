// Function definitions for the Food Class
#include "Food.h"

// getName returns a string that contains the object's "name" property value
string Food::getName() {
	return name;
}

// setName sets the value of the object's "name" property
void Food::setName(string n) {
	name = n;
}

// getQuantity returns an integer that contains the object's "quantity" property value.
int Food::getQuantity() {
	return quantity;
}

// setQuantity sets the value of the object's "quantity" property 
void Food::setQuantity(int q) {
	quantity = q;
}

// getMetric returns a string that contains the object's "metric" property value.
string Food::getMetric() {
	return metric;
}

// setMetric sets the value of the object's "metric" property
void Food::setMetric(string m) {
	metric = m;
}

// display returns a string that contains the values of the object's name, quantity, and metric properties formatted as:
// [Food - Name: %n, Quantity: %q, Metric: %m]
// ex. [Food - Name: Chips, Quantity: 2, Metric: Bags]
string Food::display() {
	string returnMessage = "[Food - Name: " + getName() + ", Quantity: ";
	returnMessage += to_string(getQuantity());
	returnMessage += ", Metric: " + getMetric() + "]";
	return returnMessage;
}
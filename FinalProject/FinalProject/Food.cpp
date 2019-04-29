#include "Food.h"

string Food::getName() {
	return name;
}

void Food::setName(string n) {
	// add input validation
	name = n;
}

int Food::getQuantity() {
	return quantity;
}

void Food::setQuantity(int q) {
	// input validation
	quantity = q;
}

string Food::getMetric() {
	return metric;
}

void Food::setMetric(string m) {
	// input validation
	metric = m;
}

string Food::display() {
	string returnMessage = "[Food - Name: " + getName() + ", Quantity: ";
	returnMessage += to_string(getQuantity());
	returnMessage += ", Metric: " + getMetric() + "]";
	return returnMessage;
}
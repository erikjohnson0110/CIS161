// Header file for my Food class.  This header contains the class definition, and function prototypes used by the class
// The Food class represents a single food item to be brought on the trip
#ifndef FOOD_H
#define FOOD_H

#include <string>

using namespace std;

// class definition.
class Food 
{
	// private members
private:
	string name;    // the name of the food
	int quantity;   // the quantity of the food item
	string metric;  // the metric used to define the quantity (ounces, bags, cans, etc)

	// public members
public:
	// Constructors
	// default constructor
	Food() {
	}

	// non-default constructor which accepts 3 arguments: a string for name, an integer for quantity, and a string for metric
	Food(string n, int q, string m) {
		setName(n);     // set name to the value of parameter n
		setQuantity(q); // set quantity to the value of parameter q
		setMetric(m);   // set metric to the value of parameter m
	}
	
	// destructor
	~Food() {
	}

	// accessors and mutators
	string getName();        // return the string value of the object's name property
	void setName(string n);  // set the food object's name

	int getQuantity();       // return the value of the object's quantity property
	void setQuantity(int q); // set the object's quantity

	string getMetric();      // return the value of the object's metric property
	void setMetric(string m);// set the object's metric property

	// helpers
	string display();        // returns a string that contain's all of the object's property values.
};

#endif // !FOOD_H

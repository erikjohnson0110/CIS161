// This header file contains all of the "global" functions that are used by the driver.
// It also contains all of the #includes needed for these functions, as well as class definitions.
// Rather than define these functions in the driver itself, I chose to define them here.
#ifndef PROGRAMFUNCTIONS_H
#define PROGRAMFUNCTIONS_H

// include standard library items
#include <list>
#include <iterator>
#include <iostream>
#include <istream>
#include <iomanip>
// include header files for classes and struct
#include "Camper.h"
#include "Food.h"
#include "FoodCamper.h"

using namespace std;

// program exceptions
// TooManyCampers exception definition
class TooManyCampersException {
private:
	string msg;                                 // exception message property

public:
	TooManyCampersException() {                 // exception constructor
		msg = "Cannot add any more campers.\n"; // set default exception message
	}
	string getMessage() {                       // function returns the exception message string
		return msg;
	}
};

// NoHappyCamperNamed exception definition
class NoHappyCamperNamedException {
private:
	string msg;                                // exception message property
public:
	NoHappyCamperNamedException() {            // default constructor
		msg = "Invalid Happy Camper Name.\n";  // sets default message
	}
	NoHappyCamperNamedException(string n) {    // non-default constructor accepts a string that contains the value that caused the exception
		msg = "No happy camper named (" + n + ") was found.\n";  // sets the exception message, and includes the string 
	}
	string getMessage() {                      // returns the exception message string
		return msg;
	}
};

// InvalidInput exception definition - for generic invalid input
class InvalidInputException {
private:
	string msg;                               // exception message
public:
	InvalidInputException() {                 // default constructor
		msg = "Error: Invalid Input Type.\n"; // sets default message
	}
	string getMessage() {                     // returns exception message.
		return msg;
	}
};

// program function prototypes
void newCamper(Camper[], int&, int&);        // function to create and save a new camper
void addFood(list<Food*>&);                  // function to create/edit/save a new food
void assignFood(Camper[], list<Food>&);      // function to assign an existing food to an existing camper
void addPayment(Camper[]);                   // function to add a payment to an existing camper
void displayMenu();                          // function that prints the menu text to the console

// program function definitions
// newCamper creates a new camper and saves them in memory
// Function parameters:
// Camper arr[] -- the array of camper objects
// int& cs -- a reference to an int that represents the current number of Campers in the camper array
// int& ms -- a reference to an int that represents the maximum size of the camper array.
void newCamper(Camper arr[], int& cs, int& ms) {
	if (cs < ms) {                             // if the number of campers in the array is less than the max size, we can add a new camper
		string inputName;                      // variable to store user input
		cout << endl;                          // display instructions to user
		cout << "-INPUT A NEW CAMPER-" << endl;
		cout << "Please enter camper name: ";

		try {                                  // try to collect user input, and catch any exceptions
			if (getline(cin, inputName)) {     // if cin successfully saves input
				                               // check each character to ensure it is alphabetic or whitespace (no numbers, symbols allowed)
				for (int i = 0; i < inputName.length(); i++) {
					if (!isalpha(inputName[i]) && !isspace(inputName[i])) {
						throw InvalidInputException();
					}
				}

				arr[cs] = Camper(inputName);   // if no exception has been thrown yet, save camper and increment counter
				cs++;

				// notify user
				cout << endl;
				cout << "***************************************************" << endl;
				cout << "Created Camper: " + arr[(cs - 1)].display() << endl;
				cout << "***************************************************" << endl;
				cout << endl;
			}
			else {   // if CIN fails, throw exception
				throw InvalidInputException();
			}
		}
		// catch any of the exceptions thrown.
		catch (InvalidInputException ex) {
			cout << endl;
			cout << ex.getMessage();  // output message to console
		}
	}
	else {                                // if the array is full
		throw TooManyCampersException();  // throw exception
	}
}

// addFood creates a new food and saves it in memory.
// if the food already exists, it allows the user to modify the existing object's properties
// Function Parameters:
// list<Food*>& l -- a reference to a list of Food pointers.  This list stores the program's food items.
void addFood(list<Food*>& l) {
	string inputType;            // variable to store user input of food type
	int inputQuantity;           // variable to store user input of quantity
	string inputMetric;          // variable to store user input of metric
	char inputSubMenu;           // variable to store user subMenu selection
	Food* tempFoodPtr = nullptr; // a pointer to a food object, initially null.  Used to instantiate a food object.

	                             // display instructions to the user
	cout << endl;
	cout << "-INPUT A NEW FOOD-" << endl;
	cout << "Please enter the type of food (Doritos, Potatos, Hot Dogs, etc.): ";
	try {                                   // try to collect user input
		if (!getline(cin, inputType)) {     // if cin cannot collect the input (not a string)
			throw InvalidInputException();  // throw an exception
		}
	}                     
	catch (InvalidInputException ex) {      // catch exception
		cout << endl;
		cout << ex.getMessage();            // display exception message
		inputType = "DEFAULT TYPE";         // set input String to "Default Type" - prevents issues with nulls, and user may change later.
	}

	bool foodExists = false;                // create a flag to indicate if food exists already, default to false.
	for (Food* f : l)                       // search list of Food pointers to detect if user input an existing food item
	{
		if (inputType._Equal(f->getName())) // compare current food object to user input, if they're equal
		{
			foodExists = true;              // set flag to true
			tempFoodPtr = f;                // set tempPointer to the current food* in the list
			cout << endl;                   // display subMenu to user
			cout << "This food type (" + inputType + ") has already been entered." << endl;
			cout << "To modify the existing food entry, press 1" << endl;
			cout << "To cancel this addition to the list, press any other key" << endl;
			cout << "INPUT SELECTION>: ";
			if (cin >> inputSubMenu) {     // if cin collects a single character
				if (inputSubMenu != '1') { // if it is NOT '1'
					cin.clear();           // clear cin
					inputSubMenu = 0;      // set subMenu to 0 - prevents any issues with comparing non numeric characters
				}
			}
			else {                        // if cin failed
				cin.clear();
				inputSubMenu = 0;         // clear cin and set input to 0 - prevents issues with comparing invalid or non numeric characters
			}
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');  // ignore any remaining garbage in cin.  prevents weird UI issues
			break;                       // food was found, break out of loop
		}
	}

	// if the food exists flag is set to true - begin subMenu 
	if (foodExists) 
	{
		if (inputSubMenu == '1') // if subMenu selection was '1'
		{
			inputSubMenu = '0';
			while (inputSubMenu != '4')  // while not exit value, display sub menu and collect input
			{
				cout << endl;
				cout << "MODIFY FOOD ITEM" << endl;
				cout << tempFoodPtr->display() << endl;
				cout << endl;
				cout << "1) Enter new Name" << endl;
				cout << "2) Enter new Quantity" << endl;
				cout << "3) Enter new Metric" << endl;
				cout << "4) Quit modifying item" << endl;
				cout << endl;
				cout << "INPUT SELECTION>: ";
				if (cin >> inputSubMenu) {         // Collect user menu selection, and validate it.
					if (inputSubMenu != '1' && inputSubMenu != '2' && inputSubMenu != '3' && inputSubMenu !='4') {
						cin.clear();
						cout << "Invalid Input";
						inputSubMenu = 0;
					}
				}
				else {                            // as before, if cin fails, clear it and set selection to 0
					cin.clear();
					inputSubMenu = 0;
				}
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

				string modifyPropertyString;   // declare variable to store modification of a "string" property
				int modifyPropertyInt;         // declare a variable to store modification of an "int" property
				switch (inputSubMenu)          // switch statement that evaluates user subMenu input
				{
					case '1':                                            // Option 1 - enter new name
						cout << endl;
						cout << "Enter new name: ";                      // prompt user
						try {                                            // try to collect input and catch any exceptions
							if (!getline(cin, modifyPropertyString)) {   // if cin fails
								throw InvalidInputException();           // throw exception
							}
							cout << endl;
							tempFoodPtr->setName(modifyPropertyString);  // set food item name property to newly collected value

							cout << endl;                                // notify user that change was a success
							cout << "***************************************************" << endl;
							cout << "Name successfully changed." << endl;
						}
						catch (InvalidInputException ex) {              // catch invalid input and display message
							cout << endl;
							cout << ex.getMessage();
						}
						break;
					case '2':                                           // Option 2 - enter new quantity
						cout << endl;
						cout << "Enter new quantity: ";                 // prompt user for input
						try {                                           // try to collect input and catch any exceptions
							if (cin >> modifyPropertyInt) {             // if cin is successful in collecting an int
								cin.clear();                            // clear out input stream - prevents issues with decimals being input, or invalid chars.
								cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
							}
							else {
								throw InvalidInputException();          // if user did not input an integer, throw exception.
							}
							cout << endl;
							tempFoodPtr->setQuantity(modifyPropertyInt);// set quantity property to newly collected value

							cout << endl;                               // notify user of success
							cout << "***************************************************" << endl;
							cout << "Quantity successfully changed." << endl;
						}
						catch (InvalidInputException ex) {             // catch and display any exception messages
							cout << endl;
							cout << ex.getMessage();
						}
						
						break; 
					case '3':                                             // Option 3 - enter a new metric property
						cout << endl;
						cout << "Enter new metric: ";                     // prompt user
						try {                                             // try to collect input, and catch any exceptions
							if (!getline(cin, modifyPropertyString)) {    // if cin fails, throw an exception
								throw InvalidInputException();
							}
							cout << endl;
							tempFoodPtr->setMetric(modifyPropertyString); // set newly collected metric value

							cout << endl;                                 // notify user of successful change
							cout << "***************************************************" << endl;
							cout << "Metric successfully changed." << endl;
						}
						catch (InvalidInputException ex) {                // catch exception and display message
							cout << endl;
							cout << ex.getMessage();
						}
						break;
					default:
						break;
				}
			}
			cout << "FINAL FOOD VALUES:" << endl;                        // when modifications are done, display final result to user
			cout << tempFoodPtr->display() << endl;
			cout << "***************************************************" << endl;
			cout << endl;
		}
	}
	else                                                                   // if the Food is NOT in the list, create a new food object.
	{
		cout << "Please enter the metric used (lbs, cans, bags, etc.): ";  // prompt user to enter metric used
		try {                                                              // try to collect metric, throw exception if invalid
			if (!getline(cin, inputMetric)) {
				throw InvalidInputException();
			}
		}
		catch (InvalidInputException ex) {                                 // catch exception and display message
			cout << endl;
			cout << ex.getMessage();                                       // with exception:
			inputMetric = "INVALID METRIC";                                // set metric value to "INVALID METRIC", prevents nulls and may be modified by user
		}

		cout << "Please enter the quantity as a whole number (1, 5, 9, etc.): ";   // prompt user to enter quantity
		try {                                                                      // try to collect quantity, throw exception if invalid
			if (cin >> inputQuantity) {
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				throw InvalidInputException();
			}
		}
		catch (InvalidInputException ex) {                                           // catch exception and display message.
			cout << endl;
			cout << ex.getMessage();                                                 // on exception:
			inputQuantity = 0;                                                       // set quantity to zero.  prevents nulls and is changeable later by user
		}

		l.push_front(new Food(inputType, inputQuantity, inputMetric));               // create new Food object, and add it to the list
		                                                                             // display results to user. 
		cout << endl;
		cout << "***************************************************" << endl;
		cout << "Food Created - " + l.front()->display() << endl;
		cout << "***************************************************" << endl;
		cout << endl;
	}
}

// assignFood assigns an existing food item to an existing camper
// Function Parameters:
// Camper *arr -- a pointer to the Camper array
// int as -- an int that represents the max size of the previous array
// list<Food*>& l -- a reference to a list of Food pointers
// list<FoodCamper>& fc -- a reference to the FoodCamper list
void assignFood(Camper *arr, int as, list<Food*>& l, list<FoodCamper>& fc) {
	bool foundCamper = false;       // flag to store if camper was found in the array
	bool foundFood = false;         // flag to store if food was found in the array
	string inputName;               // store input from user
	string inputFood;               // store input from user

	Food* tempFood = nullptr;       // pointer to a Food object, initialized as a nullptr
	Camper* tempCamper = nullptr;   // pointer to a Camper object, initialized as a nullptr
	FoodCamper* tempFC = nullptr;   // pointer to a FoodCamper struct, initialized as a nullptr

	cout << endl;                   // prompt user for Camper name input
	cout << "-ASSIGN FOOD TO CAMPER-" << endl;
	cout << "Please enter a camper's name: ";
	try {                                     // try to collect user input, catch exception
		if (!(getline(cin, inputName))) {     // if cin fails
			throw InvalidInputException();    // throw an exception
		}
		cin.clear();                          // clear cin to prevent any issues
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	}
	catch (InvalidInputException ex) {        // catch exception, clear cin, and display exception message
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << endl;
		cout << ex.getMessage();
	}

	for (int i = 0; i < as && !foundCamper; i++) {   // iterate through camper array, until camper is found
		string temp = arr[i].getName();              // get the name of the current camper in the array

		if (temp._Equal(inputName)) {                // compare it to user input, if they match
			foundCamper = true;                      // set flag to true
			tempCamper = &arr[i];                    // set pointer to current camper's memory address
		}
	}

	if (foundCamper) {                               // if camper was found, begin to assign food
		cout << "Assign food to camper: " + inputName << endl;  // prompt user 
		cout << endl;
		cout << "Enter Food to Assign: ";
		try {                                        // try to collect food name input and catch exceptions
			if (!getline(cin, inputFood)) {          // if cin fails, throw exception
				throw InvalidInputException();
			}
		}
		catch (InvalidInputException ex) {           // catch exception, clear cin, and display message.
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << endl;
			cout << ex.getMessage();
		}

		for (Food* f : l) {                        // iterate through each food in the list
			if (inputFood._Equal(f->getName())) {  // if the current food matches the input name
				foundFood = true;                  // set flag to true
				tempFood = f;                      // assign pointer to current food pointer from list
			}
		}

		if (foundFood) {                          // if a food was found
			tempFC = new FoodCamper();            // create new food camper struct
			tempFC->camper = *tempCamper;         // assign the found camper
			tempFC->food = *tempFood;             // assign the found food
			fc.push_front(*tempFC);               // add the FoodCamper struct to the FoodCamper list

			cout << endl;                         // prompt user with success message, and food camper status.
			cout << "***************************************************" << endl;
			cout << "Food Item (" + tempFood->getName() + ") assigned to (" + tempCamper->getName() + ")" << endl;
			cout << "***************************************************" << endl;
			cout << endl;
		}
		else {                                     // if food was NOT found, notify user
			cout << "Food Item Not Found" << endl;
			cout << endl;
		}
	}
	else {                                         // if camper was NOT found, throw exception
		throw NoHappyCamperNamedException(inputName);
	}
}

// addPayment function assigns a payment to an existing camper
// Function Parameters:
// Camper *arr -- a pointer to the array of campers
// int as -- an int that represents the max size of the array passed
void addPayment(Camper *arr, int as) { 
	bool foundCamper = false;      // flag for if camper was found
	int camperIndex = 0;           // variable to store the index of the found camper
	string inputName;              // store the users input for camper name

	cout << endl;                  // prompt user for input
	cout << "-ASSIGN PAYMENT FOR CAMPER-" << endl;
	cout << "Please enter a camper's name: ";
	try {                                   // try to collect input, catch exception
		if (!getline(cin, inputName)) {     // if cin fails, throw an exception
			throw InvalidInputException();
		}
	}
	catch (InvalidInputException ex) {      // catch an exception, clear cin, and display exception message
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << endl;
		cout << ex.getMessage();
	}

	for (int i = 0; i < as && !foundCamper; i++) {   // iterate through array of campers until camper found
		string temp = arr[i].getName();              // store current camper's name 

		if (temp._Equal(inputName)) {                // compare current camper name to input
			foundCamper = true;                      // if they match, set flag to true
			camperIndex = i;                         // record index number
		}
	}

	if (foundCamper) {                              // if the camper was found
		arr[camperIndex].pay();                     // call pay function for the found camper

		cout << endl;                               // display message to user
		cout << "***************************************************" << endl;
		cout << "Payment success: " + arr[camperIndex].getName() + " has paid." << endl;
		cout << "***************************************************" << endl;
		cout << endl;
	}
	else {                                          // if camper not found, throw exception
		throw NoHappyCamperNamedException(inputName);
	}
}

// displayMenu function only displays menu text to the console.
void displayMenu() 
{
	cout << "***************************************************" << endl;
	cout << "Happy Camper - Camp Manager" << endl;
	cout << "***************************************************" << endl;
	cout << endl;
	cout << "MENU" << endl;
	cout << "1) Add new camper" << endl;
	cout << "2) Add new food" << endl;
	cout << "3) Assign food to camper" << endl;
	cout << "4) Add payment for camper" << endl;
	cout << "5) Exit program" << endl;
	cout << endl;
	cout << "INPUT SELECTION>: ";
}
#endif // !PROGRAMFUNCTIONS_H


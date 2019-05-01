//============================================================================
// Name        : CamperDriverJohnson.cpp
// Author      : Erik E Johnson
// Date        : 4/24/2019
// Course      : CIS 161 - C++
// Version     : 1.0
// Copyright   : This is my own original work based on specifications issued by our instructor
// Description : This program allows the user to input campers, and foods into
//               the program for managing a camping trip.  The user may also
//               assign foods to campers, and add payments for campers.
//============================================================================
#include <iomanip>
#include "ProgramFunctions.h"

using namespace std;

int main()
{
	// declare data structures used by the program
	Camper* happyCampers = nullptr;   // nullptr that will point to a dynamically allocated array of Camper objects
	list<Food*> foodList;             // a list of pointers to Food objects
	list<FoodCamper> foodCamperList;  // a list of FoodCamper structs

	int numCampersInput = -1;         // variable to store input from user, initialized to -1
	bool numCampersIsValid = false;   // flag for validating the number of campers, initialized to false
	int max = 0;                      // variable to store max number of campers, from user input
	int current = 0;                  // variable to store the number of campers currently stored in the array

	int userMenuSelection = 0;        // variable to store user menu selection input
	const int EXIT_VALUE = 5;         // constant for the menu exit value

	// collect number of campers while input validation flag is not true
	while (!numCampersIsValid)
	{
		cout << "How many campers are going on your trip? >: ";

		try {                                 // try to collect input from the user
			if (cin >> numCampersInput) {     // if the user enters an integer
				if (numCampersInput < 0) {    // if the input is negative
					cout << endl;             // tell user they cannot input negatives, and throw exception
					cout << "Negative number not allowed." << endl;
					throw InvalidInputException();
				}
				else {                        // if input is an integer and is positive, set flag to true
					numCampersIsValid = true;
				}
			}
			else {                            // if cin fails to collect an integer, throw exception
				throw InvalidInputException();
			}
		}
		catch (InvalidInputException ex) {      // catch exception, clear input stream, and display error msg to user
			cout << ex.getMessage();
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		cout << endl;
		cout << endl;
	}
	// NOTE: clearing out input stream - This helps with issues where the user input a decimal in the previous input.
	// A decimal will be truncated and stored as a valid integer, so the program will proceed, however there will be something 
	// in the input stream that causes the next input block to enter an infinite loop of input errors (due to the decimal??  end line char?).  
	// Either way, this solves the issue.
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');


	// dynamically allocate array of Campers
	max = numCampersInput;            // set max variable to the number input by the user
	happyCampers = new Camper[max];

	// main body of program -  while the user has not input the exit value
	while (userMenuSelection != EXIT_VALUE)
	{
		// display menu and collect user selection
		displayMenu();
		bool menuSelectIsValid = false;  // menu selection validation flag set to false
		while (!menuSelectIsValid)
		{
			try {                                                       // try to collect menu selection from cin
				if (cin >> userMenuSelection) {                         // if the user inputs an integer
					if (userMenuSelection > 0 && userMenuSelection < 6) // if the input is between 1 and 5
					{
						menuSelectIsValid = true;                       // then selection is valid; set flag to true
					}
					else                                                // if not between 1 and 5, notify user and set flag to false
					{
						cout << endl;
						cout << "INVALID INPUT: Selection must be between 1 and 5.  Please make another selection." << endl;
						cout << "INPUT SELECTION>: ";
						//invalid input
						userMenuSelection = false;
					}
				}
				else {                                              // if cin could not collect an integer, throw an exception
					throw InvalidInputException();
				}

			}
			catch (InvalidInputException ex) {                     // catch exception, notify user, clear cin
				cout << endl;
				cout << "INVALID INPUT: Selection must be between 1 and 5.  Please make another selection." << endl;
				cout << "INPUT SELECTION>: ";
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

		switch (userMenuSelection)  // switch statement that evaluates validated user menu selection input
		{
			case 1:                 //case 1 - try to add a new camper, catch exception
				try 
				{
					newCamper(happyCampers, current, max);
				}
				catch (TooManyCampersException ex) 
				{
					cout << ex.getMessage();
				}
				break;
			case 2:                 // case 2 - add food
				addFood(foodList);
				break;
			case 3:                 // case 3 - try to assign food to camper, catch exception
				try {
					assignFood(happyCampers, current, foodList, foodCamperList);
				}
				catch (NoHappyCamperNamedException ex) {
					cout << ex.getMessage();
				}
				break;
			case 4:                 // case 4 - try to add payment for camper, catch exception
				try {
					addPayment(happyCampers, current);
				}
				catch (NoHappyCamperNamedException ex) {
					cout << ex.getMessage();
				}
				break;
			case 5:
				// exit
				break;
			default:
				break;
		}

	}

	// user has selected to exit.  Thank them and exit program
	cout << "THANK YOU FOR USING OUR PROGRAM." << endl;
	cout << "PRESS ANY KEY TO EXIT";
	cin.get();

	return 0;
}
//============================================================================
// Name        : CamperDriverJohnson.cpp
// Author      : Erik E Johnson
// Date        : 4/24/2019
// Course      : CIS 161 - C++
// Version     : 1.0
// Copyright   : 
// Description : 
//============================================================================
#include <iomanip>
#include "ProgramFunctions.h"

using namespace std;

int main()
{
	Camper* happyCampers = nullptr;
	list<Food*> foodList;
	list<FoodCamper> foodCamperList;

	// number of campers
	int numCampersInput = -1;
	bool numCampersIsValid = false;
	int max = 0;
	int current = 0;

	int userMenuSelection = 0;
	const int EXIT_VALUE = 5;

	// collect number of campers
	while (!numCampersIsValid)
	{
		cout << "How many campers are going on your trip? >: ";

		try {
			if (cin >> numCampersInput) {
				if (numCampersInput < 0) {
					cout << endl;
					cout << "Negative number not allowed." << endl;
					throw InvalidInputException();
				}
				else {
					numCampersIsValid = true;
				}
			}
			else {
				throw InvalidInputException();
			}
		}
		catch (InvalidInputException ex) {
			cout << ex.getMessage();
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		cout << endl;
		cout << endl;
	}
	// clear out input stream.  This helps with issues where the user input a decimal in the previous input.
	// A decimal will be truncated and stored as a valid integer, so the program will proceed, however there will be something 
	// in the input stream that causes the next input block to enter an infinite loop of input errors (due to the decimal??  end line char?).  
	// Either way, this solves the issue.
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');


	// dynamically allocate array of Campers
	max = numCampersInput;
	happyCampers = new Camper[max];

	// main body of program
	while (userMenuSelection != EXIT_VALUE)
	{
		// display menu and collect user selection
		displayMenu();
		bool menuSelectIsValid = false;
		while (!menuSelectIsValid)
		{
			try {
				if (cin >> userMenuSelection) {
					if (userMenuSelection > 0 && userMenuSelection < 6)
					{
						menuSelectIsValid = true;
					}
					else
					{
						cout << endl;
						cout << "INVALID INPUT: Selection must be between 1 and 5.  Please make another selection." << endl;
						cout << "INPUT SELECTION>: ";
						//invalid input
						userMenuSelection = false;
					}
				}
				else {
					throw InvalidInputException();
				}

			}
			catch (InvalidInputException ex) {
				cout << endl;
				cout << "INVALID INPUT: Selection must be between 1 and 5.  Please make another selection." << endl;
				cout << "INPUT SELECTION>: ";
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

		switch (userMenuSelection) 
		{
			case 1:
				//add new camper
				try 
				{
					newCamper(happyCampers, current, max);
				}
				catch (TooManyCampersException ex) 
				{
					cout << ex.getMessage();
				}
				break;
			case 2:
				addFood(foodList);
				break;
			case 3:
				try {
					assignFood(happyCampers, current, foodList, foodCamperList);
				}
				catch (NoHappyCamperNamedException ex) {
					cout << ex.getMessage();
				}
				break;
			case 4:
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

	cout << "THANK YOU FOR USING OUR PROGRAM." << endl;
	cout << "PRESS ANY KEY TO EXIT";
	cin.get();

	return 0;
}
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
	int max = 0;
	int current = 0;

	int userMenuSelection = 0;
	const int EXIT_VALUE = 5;

	// collect number of campers
	while (numCampersInput < 0)
	{
		cout << "How many campers are going on your trip? >: ";
		cin >> numCampersInput;
		if (numCampersInput < 0) {
			cout << endl;
			cout << "Negative number not allowed.";
		}
		cout << endl;
		cout << endl;
	}

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
			cin >> userMenuSelection;
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

	cin.ignore();
	cin.get();

	return 0;
}
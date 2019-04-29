#ifndef PROGRAMFUNCTIONS_H
#define PROGRAMFUNCTIONS_H

#include <list>
#include <iterator>
#include <iostream>
#include <istream>
#include <iomanip>
#include "Camper.h"
#include "Food.h"
#include "FoodCamper.h"

using namespace std;

// program exceptions
class TooManyCampersException {
private:
	string msg;

public:
	TooManyCampersException() {
		msg = "Cannot add any more campers.\n";
	}
	string getMessage() {
		return msg;
	}
};

class NoHappyCamperNamedException {
private:
	string msg;
public:
	NoHappyCamperNamedException() {
		msg = "Invalid Happy Camper Name.\n";
	}
	NoHappyCamperNamedException(string n) {
		msg = "No happy camper named (" + n + ") was found.\n";
	}
	string getMessage() {
		return msg;
	}
};

// program function prototypes
void newCamper(Camper[], int&, int&);
void addFood(list<Food*>&);
void assignFood(Camper[], list<Food>&);
void addPayment(Camper[]);
void displayMenu();

// program function definitions

void newCamper(Camper arr[], int& cs, int& ms) {
	if (cs < ms) {
		string inputName;
		cout << endl;
		cout << "-INPUT A NEW CAMPER-" << endl;
		cout << "Please enter camper name: ";
		cin.ignore();
		getline(cin, inputName);
		arr[cs] = Camper(inputName);
		cs++;

		cout << endl;
		cout << "***************************************************" << endl;
		cout << "Created Camper: " + arr[(cs - 1)].display() << endl;
		cout << "***************************************************" << endl;
		cout << endl;
	}
	else {
		throw TooManyCampersException();
	}
}

void addFood(list<Food*>& l) {
	string inputType;
	//string inputQuantityString;
	int inputQuantity;
	string inputMetric;
	char inputSubMenu;
	Food* tempFoodPtr = nullptr;

	cout << endl;
	cout << "-INPUT A NEW FOOD-" << endl;
	cout << "Please enter the type of food (Doritos, Potatos, Hot Dogs, etc.): ";
	cin.ignore();
	getline(cin, inputType);

	bool foodExists = false;
	for (Food* f : l) 
	{
		if (inputType._Equal(f->getName())) 
		{
			foodExists = true;
			tempFoodPtr = f;
			cout << endl;
			cout << "This food type (" + inputType + ") has already been entered." << endl;
			cout << "To modify the existing food entry, press 1" << endl;
			cout << "To cancel this addition to the list, press any other key" << endl;
			cout << "INPUT SELECTION>: ";
			cin.get(inputSubMenu);
			cout << endl;
			cout << "You chose: " + inputSubMenu;
			break;
		}
	}

	if (foodExists) 
	{
		if (inputSubMenu == '1') 
		{
			inputSubMenu = 0;
			while (inputSubMenu != '4') 
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
				cin >> inputSubMenu;

				while (inputSubMenu < '1' && inputSubMenu > '4') 
				{
					cout << "INVALID SELECTION. Please select a value of 1, 2, 3, or 4" << endl;
					cout << "INPUT SELECTION>: ";
					cin >> inputSubMenu;
				}

				string modifyPropertyString;
				int modifyPropertyInt;
				switch (inputSubMenu) 
				{
					case '1':
						// enter new name
						cout << endl;
						cout << "Enter new name: ";
						cin.ignore();
						getline(cin, modifyPropertyString);
						cout << endl;
						tempFoodPtr->setName(modifyPropertyString);

						cout << endl;
						cout << "***************************************************" << endl;
						cout << "Name successfully changed." << endl;
						break;
					case '2':
						// enter new quantity
						cout << endl;
						cout << "Enter new quantity: ";
						cin >> modifyPropertyInt;
						cout << endl;
						tempFoodPtr->setQuantity(modifyPropertyInt);

						cout << endl;
						cout << "***************************************************" << endl;
						cout << "Quantity successfully changed." << endl;
						break;
					case '3':
						// enter new metric
						cout << endl;
						cout << "Enter new metric: ";
						cin.ignore();
						getline(cin, modifyPropertyString);
						cout << endl;
						tempFoodPtr->setMetric(modifyPropertyString);

						cout << endl;
						cout << "***************************************************" << endl;
						cout << "Metric successfully changed." << endl;
						break;
					default:
						break;
				}
			}
			cout << "FINAL FOOD VALUES:" << endl;
			cout << tempFoodPtr->display() << endl;
			cout << "***************************************************" << endl;
			cout << endl;
		}
	}
	else
	{
		cout << "Please enter the metric used (lbs, cans, bags, etc.): ";
		getline(cin, inputMetric);
		cout << "Please enter the quantity as a whole number (1, 5, 9, etc.): ";
		cin >> inputQuantity;
		//Food temp(inputType, inputQuantity, inputMetric);
		l.push_front(new Food(inputType, inputQuantity, inputMetric));

		cout << endl;
		cout << "***************************************************" << endl;
		cout << "Food Created - " + l.front()->display() << endl;
		cout << "***************************************************" << endl;
		cout << endl;
	}
}

void assignFood(Camper *arr, int as, list<Food*>& l, list<FoodCamper>& fc) {
	bool foundCamper = false;
	bool foundFood = false;
	string inputName;
	string inputFood;

	Food* tempFood = nullptr;
	Camper* tempCamper = nullptr;
	FoodCamper* tempFC = nullptr;

	cout << endl;
	cout << "-ASSIGN FOOD TO CAMPER-" << endl;
	cout << "Please enter a camper's name: ";
	cin >> inputName;

	for (int i = 0; i < as && !foundCamper; i++) {
		string temp = arr[i].getName();

		if (temp._Equal(inputName)) {
			// camper found
			foundCamper = true;
			tempCamper = &arr[i];
		}
	}

	if (foundCamper) {
		// assign food logic
		cout << "Assign food to camper: " + inputName << endl;
		cout << "Enter Food to Assign: ";
		cin.ignore();
		getline(cin, inputFood);

		for (Food* f : l) {
			if (inputFood._Equal(f->getName())) {
				foundFood = true;
				tempFood = f;
			}
		}

		if (foundFood) {
			tempFC = new FoodCamper();
			tempFC->camper = *tempCamper;
			tempFC->food = *tempFood;
			fc.push_front(*tempFC);

			cout << endl;
			cout << "***************************************************" << endl;
			cout << "Food Item (" + tempFood->getName() + ") assigned to (" + tempCamper->getName() + ")" << endl;
			cout << "***************************************************" << endl;
			cout << endl;
		}
		else {
			cout << "Food Item Not Found" << endl;
			cout << endl;
		}
	}
	else {
		throw NoHappyCamperNamedException(inputName);
	}
}

void addPayment(Camper *arr, int as) {
	bool foundCamper = false;
	int camperIndex = 0;
	string inputName;

	cout << endl;
	cout << "-ASSIGN PAYMENT FOR CAMPER-" << endl;
	cout << "Please enter a camper's name: ";
	cin.ignore();
	getline(cin, inputName);

	for (int i = 0; i < as && !foundCamper; i++) {
		string temp = arr[i].getName();

		if (temp._Equal(inputName)) {
			// camper found
			foundCamper = true;
			camperIndex = i;
		}
	}

	if (foundCamper) {
		// assign food logic
		arr[camperIndex].pay();

		cout << endl;
		cout << "***************************************************" << endl;
		cout << "Payment success: " + arr[camperIndex].getName() + " has paid." << endl;
		cout << "***************************************************" << endl;
		cout << endl;
	}
	else {
		throw NoHappyCamperNamedException(inputName);
	}
}

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

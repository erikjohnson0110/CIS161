#ifndef CAMPER_H
#define CAMPER_H

#include <string>

using namespace std;

class Camper 
{
private:
	string name;
	bool paid;

public:
	Camper() 
	{
		name = "A Happy Camper";
		paid = false;
	}

	Camper(string n) 
	{
		name = n;
		paid = false;
	}

	~Camper() {
	}

	string getName();
	void pay();
	bool hasPaid();
	string display();
};

#endif // !CAMPER_H


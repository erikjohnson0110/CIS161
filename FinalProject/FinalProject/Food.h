#ifndef FOOD_H
#define FOOD_H

#include <string>

using namespace std;

class Food 
{
private:
	string name;
	int quantity;
	string metric;
public:
	// constructors
	Food() {
	}

	Food(string n, int q, string m) {
		setName(n);
		setQuantity(q);
		setMetric(m);
	}
	
	// destructor
	~Food() {
	}

	// accessors and mutators
	string getName();
	void setName(string n);

	int getQuantity();
	void setQuantity(int q);

	string getMetric();
	void setMetric(string m);

	// helpers
	string display();
};

#endif // !FOOD_H

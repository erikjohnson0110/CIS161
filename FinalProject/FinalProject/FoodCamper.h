// Header file that defines the FoodCamper struct
// The FoodCamper struct represents a Food item associated with a Camper used to assign foods to campers.
#ifndef FOODCAMPER_H
#define FOODCAMPER_H

using namespace std;

// struct definition
struct FoodCamper {
	Food food;     // food object
	Camper camper; // camper object
};

#endif // !FOODCAMPER_H


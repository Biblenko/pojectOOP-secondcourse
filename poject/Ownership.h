#pragma once

#include "Adress.h"
#include "User.h"

class Ownership
{
	User owner;
	Adress adresOfOwn;
	short numberOfRooms;
	long totalCost;
	bool availableForRent;
	short houseNumber;
	short numberOfFloors;
};


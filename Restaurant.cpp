#include "Restaurant.h"

// Default Constructor
Restaurant::Restaurant()
{
	restaurantName = "";
	postalCode = 650367;	// Doxxing myself
}

// Parameterized Constructor
Restaurant::Restaurant(string aRestaurantName, int aPostalCode)
{
	restaurantName = aRestaurantName;
	postalCode = aPostalCode;
}

// Destructor
Restaurant::~Restaurant()
{
}

// Returns restaurant name
// Pre : ~
// Post: Restaurant name
string Restaurant::getRestaurantName()
{
	return restaurantName;
}

// Returns postalCode
// Pre : ~
// Post: postalCode
int Restaurant::getPostalCode()
{
	return postalCode;
}

void Restaurant::printMenu()
{
	cout << "PRINTING MENU" << endl
		<< "=============" << endl;
	restaurantMenu.printInOrder();
	cout <<"=============" << endl; 
}


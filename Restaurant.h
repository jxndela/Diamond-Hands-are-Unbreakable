#pragma once
#include <iostream>
#include <string>
#include "OrderQueue.h"
#include "RestaurantStaff.h"
#include "Order.h"
#include "FoodItemAVL.h"

using namespace std;

// Forward declaration
class Order;
class OrderQueue;

class Restaurant
{
private:

	string restaurantName;	// Store restaurant name
	int postalCode;			// Store restaurant postal code
	OrderQueue* incomingOrder;
	FoodItemAVL restaurantMenu;

public:
	// Default Constructor
	Restaurant();
	// Parameterized Constructor
	Restaurant(string aRestaurantName, int aPostalCode);
	// Destructor
	~Restaurant();
	// Returns restaurant name
	// Pre : ~
	// Post: Restaurant name
	string getRestaurantName();
	// Returns postalCode
	// Pre : ~
	// Post: postalCode
	int getPostalCode();

	void printMenu();

	OrderQueue* getIncomingOrder()
	{
		return incomingOrder;
	}

	FoodItemAVL* getRestaurantMenuPointer()
	{
		FoodItemAVL* aPointer = &restaurantMenu;
		return aPointer;
	}
};


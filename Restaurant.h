#pragma once
#include <iostream>
#include <string>

using namespace std;

class Restaurant
{
private:

	string restaurantName;	// Store restaurant name
	int postalCode;			// Store restaurant postal code
	//OrderQueue incomingOrder;
	// Contain FoodItem AVL Tree

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

	// Get the order queue pointer from restaurant
	// Pre : Order not queue not empty
	// Post: Get pointer to order queue to save space complexity
	//OrderQueue* getRestaurantOrders();



};


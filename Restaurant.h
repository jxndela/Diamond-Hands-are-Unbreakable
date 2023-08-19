#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
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

// Forward Declaration
class Restaurant;
class FoodItemAVL;

// Constants
const int STACK_MAX_SIZE = 100;
const int MAX_RESTAURANTS = 100;

class RestaurantArray
{
private:
	// Restaurant item array
	Restaurant allRestaurants[MAX_RESTAURANTS];
	// Number of restaurants
	int numberOfRestaurants = 0;


public:

	// Constructor
	RestaurantArray();
	// Destructor
	~RestaurantArray();
	// Get method - no. of restaurants
	int getNumberOfRestaurants();
	// Get method - Pointer of specific restaurant
	Restaurant* getRestaurant(int aIndexPosition);
	// Get method - Pointer to restaurants[MAX_RESTAURANTS]
	Restaurant* GetAllRestaurant();
	// Add new restaurant add a specific index position
	void addRestaurant(Restaurant& aRestaurant, int& aIndexPosition);
	// Print Restaurant
	void printRestaurants();
	// Read .txt file
	void readRestaurantFile();
	// Write to Food Items
	void writeRestaurantFile();
	void writeFoodItemsRecursive(ofstream& aOutFile, AVLNode* aNode,int& aIndexPosition);
	void writeFoodItemsAVL();


};


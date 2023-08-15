#pragma once
#include <iostream>
#include <fstream>	// For reading writing files
#include <sstream>	
#include <string>
#include "OrderQueue.h"
#include "RestaurantStaff.h"
#include "Order.h"
#include "FoodItemAVL.h"
#include "Restaurant.h"

using namespace std;

// ForwardDeclaration
class Restaurant;
// Constants
const int STACK_MAX_SIZE = 100;
const int MAX_RESTAURANTS = 100;

class RestaurantArray
{
private:
	// Restaurant item array
	Restaurant restaurants[MAX_RESTAURANTS];
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
	void writeFoodItemsAVL(ofstream& aOutFile, AVLNode* aNode);
};


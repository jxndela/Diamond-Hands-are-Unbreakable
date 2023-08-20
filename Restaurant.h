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
class FoodItemAVL;

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

	// Prints menu
	// Pre : ~
	// Post: Prints the entirety of the restaurants menu
	void printMenu();

	// Get incoming Order
	// Pre : ~
	// Post: Get incoming order queue pointer
	OrderQueue* getIncomingOrder();

	// Get restaurant menu
	// Pre : ~
	// Post: Get restaurant menu pointer
	FoodItemAVL* getRestaurantMenuPointer();
};

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
	// Pre : ~
	// Post: Prints all the restaurants that were saved
	void printRestaurants();

	// Read .txt file
	// Pre : ~
	// Post: Create restaurant objects after reading information
	// Post: Also read all food items and add them to respective restaurants
	void readRestaurantFile();

	// Save restaurants by writing to file
	// Pre : ~
	// Post: Restaurant information are stored inside a txt file
	void writeRestaurantFile();

	// Recursive function  to save the food items
	// Base Case : Current node = nullptr
	// Post: Else write out which restaurant it belongs to through index position, and store information
	void writeFoodItemsRecursive(ofstream& aOutFile, AVLNode* aNode,int& aIndexPosition);

	// Save food items
	// Pre :  ~
	// Post: Calls recursive function for each restaurant, and distributes index position for each of them
	//		 so that we can map which items belong to which restaurants
	void writeFoodItemsAVL();
};
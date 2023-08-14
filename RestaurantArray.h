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



const int STACK_MAX_SIZE = 100;
const int MAX_RESTAURANTS = 100;

class RestaurantArray
{
private:

	Restaurant restaurants[MAX_RESTAURANTS];
	int numberOfRestaurants = 0;

public:

	RestaurantArray();
	~RestaurantArray();
	void addRestaurant(Restaurant& aRestaurant, int& aIndexPosition);
	Restaurant* getRestaurant(int aIndexPosition);
	void readRestaurantFile();
	void printRestaurants();


};


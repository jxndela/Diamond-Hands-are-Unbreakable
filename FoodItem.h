#pragma once
#include <iostream>
#include <string>

using namespace std;

class FoodItem
{
private:

	string foodItemName;			// Stores name of food item
	string foodItemDescription;		// Stores description of food item
	string category;				// Stores the category of food that the item belongs to
	double price;					// Stores price of food item
	bool isAvailable;				// Stores availability of food item

public:
	// Default constructor
	FoodItem();

	// Parameterized constructor
	// isAvaiable is set to TRUE by default
	FoodItem(string aName, string aDescription, string aCategory, double aPrice);

	// Destructor
	~FoodItem();

	// Function to set price of food item
	// Pre : ~
	// Post: Price will be changed
	void setFoodItemPrice(double price);

	// Function to set availability
	// Pre : ~
	// Post: Availability will be changed
	void setAvailability(bool aAvailableStatus);

	// Function to get name of food item
	// Pre : ~
	// Post: Retrieves the name of the food item
	string getName();

	// Function to get name of food item
	// Pre : ~
	// Post: Retrieves the name of the food item
	string getFoodDescription();

	// Function to get name of food item
	// Pre : ~
	// Post: Retrieves the name of the food item
	string getCategory();
	 
	// Function to get price of food item
	// Pre : ~ 
	// Post: Retrieves price of the food item
	double getPrice();

	// Function to get availability of food item
	// Pre : ~ 
	// Post: Retrieves availability of the food item
	bool getAvailability();

};


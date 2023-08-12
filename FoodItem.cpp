#include "FoodItem.h"


// Default constructor
FoodItem::FoodItem()
{
	foodItemName = "";
	foodItemDescription = "";
	category = "";
	price = 0;
	isAvailable = false;
}

// Parameterized constructor
// isAvaiable is set to TRUE by default
FoodItem::FoodItem(string aName, string aDescription, string aCategory, double aPrice)
{
	foodItemName = aName;
	foodItemDescription = aDescription;
	category = aCategory;
	price = aPrice;
	isAvailable = true;
}

// Destructor
FoodItem::~FoodItem()
{
}

// Function to set price of food item
// Pre : ~
// Post: Price will be changed
void FoodItem::setFoodItemPrice(double aPrice)
{
	price = aPrice;
}

// Function to set availability
// Pre : ~
// Post: Availability will be changed
void FoodItem::setAvailability(bool aAvailableStatus)
{
	isAvailable = aAvailableStatus;
}

// Function to get name of food item
// Pre : ~
// Post: Retrieves the name of the food item
string FoodItem::getName()
{
	return foodItemName;
}

// Function to get FoodDescription
// Pre : ~
// Post: Retrieves the FoodDescription
string FoodItem::getFoodDescription()
{
	return foodItemDescription;
}

// Function to get Category
// Pre : ~
// Post: Retrieves the name of Category
string FoodItem::getCategory()
{
	return category;
}

// Function to get price of food item
// Pre : ~ 
// Post: Retrieves price of the food item
double FoodItem::getPrice()
{
	return price;
}

// Function to get availability of food item
// Pre : ~ 
// Post: Retrieves availability of the food item
bool FoodItem::getAvailability()
{
	return isAvailable;
}
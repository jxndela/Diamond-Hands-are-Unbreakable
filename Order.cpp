/*
 * T03 Jonathan Ho S10246045 Ong Jun Jie S10240117
 * Done by Ong Jun Jie
 */
#include "Order.h"

// Default constructor
Order::Order()
{
	customerPointer = nullptr;
	restaurantPointer = nullptr;
	for (int i = 0; i < ORDER_MAX_SIZE; i++)
	{
		orderedItems[i] = nullptr;
	}
	customerName = "";
	restaurantName = "";
	customerPostalCode = 650367;
	int size = 0;
}

// Parameterized Constructor
Order::Order(Customer* aCustomerPointer, Restaurant* aRestaurant)
{
	customerPointer = aCustomerPointer;
	restaurantPointer = aRestaurant;
	// Initalize blank array full of null pointers
	// Array type is of fooditem pointer, where size = ORDER_MAX_SIZE
	for (int i = 0; i < ORDER_MAX_SIZE; i++)
	{
		orderedItems[i] = nullptr;
	}
	// dereference pointer
	customerName = aCustomerPointer->getCustomerName();
	customerPostalCode = aCustomerPointer->getCustomerPostalCode();
	restaurantName = aRestaurant->getRestaurantName();
	// 
	size = 0;
}

// Destructor
Order::~Order()
{
}

// Get ordered items
// Pre : ~
// Post: aFoodPointerArray contains all ordered item pointers
void Order::getOrderedItems(FoodItem* aFoodPointerArray[ORDER_MAX_SIZE])
{
	aFoodPointerArray = orderedItems;
}

// Get order status 
// Pre : ~
// Post: Get order status
string Order::getOrderStatus()
{
	return orderStatus;
}

// Get customer name
// Pre : ~
// Post: Get customer name
string Order::getCustomerName()
{
	return customerName;
}

// Get customer postalcode
// Pre : ~
// Post: Get customer postalcode
int Order::getCustomerPostalCode()
{
	return customerPostalCode;
}

// Get the size
// Pre : ~
// Post: Get size
int Order::getSize()
{
	return size;
}

// Get the Restaurant Pointer
// Pre : ~
// Post: Get Restaurant Pointer
Restaurant* Order::getRestaurantPointer()
{
	return restaurantPointer;
}

// Set the two main parties involved in an order, customer & restaurant
// Pre : ~
// Post: customer pointer and restaurant pointer are set
void Order::setPartyInformation(Customer* aCustomer, Restaurant* aRestaurant)
{
	customerPointer = aCustomer;
	restaurantPointer = aRestaurant;
}

// Set postal code of customer
// Pre : ~
// Post: Set customer postal code
void Order::setCustomerPostalCode(int aPostalCode)
{
	customerPostalCode = aPostalCode;
}

// Set name of customer
// Pre : ~
// Post: Set customer name
void Order::setCustomerName(string aName)
{
	customerName = aName;
}

// Set name of restaurant
// Pre : ~
// Post: Set restaurant name
void Order::setRestaurantName(string aName)
{
	restaurantName = aName;
}

// Set method for order status from restaurant
// Pre  : ~
// Post : order status changed to completed
void Order::setOrderStatusComplete()
{
	orderStatus = "Completed";
}

// checks if ordered items is full
// Pre : ~
// Post: Returns true if full, false otherwise
bool Order::isFull()
{
	return size == ORDER_MAX_SIZE;
}

// Add food item into orderedItems
// Pre : foodOrderedItems must not be full
// Post: 
bool Order::addFoodItem(FoodItem* aFoodItemPointer)
{
	// If full, exit right away
	if (isFull())
		return false;

	// Else, there should be space proceed to add to list, find next empty space
	for (int i = 0; i < ORDER_MAX_SIZE; i++)
	{
		// If index in orderedItems is empty, add it
		if (orderedItems[i] == nullptr)
		{
			orderedItems[i] = aFoodItemPointer;
			size++;
			return true;
		}
		// Else, it is full do not add - go next
	}
	return true;
}

// Remove food item from order
// Pre : food item must exist within the order
// Post : Return success or error message
bool Order::removeFoodItem(FoodItem* aFoodItemPointer)
{
	// Iterate through array
	for (int i = 0; i < ORDER_MAX_SIZE; i++)
	{
		// If food item mathes
		if (orderedItems[i] == aFoodItemPointer)
		{
			orderedItems[i] = nullptr;
			cout << "FoodItem removed Succesfully" << endl;
			return true;
		}
	}
	// Else not found
	cout << "FoodItem is not found within order array" << endl;
	return false;
}

// Print all information and food items in order of first occurence
// Pre : ~
// Post: ~
void Order::printOrderInformation()
{
	// Step 1: View information
	cout << "=========================================" << endl;
	cout << "Showing Order and Customer Information..." << endl;
	cout << "Order Status : " << orderStatus << endl;
	cout << "Restaurant Name : " << restaurantName << endl;
	cout << "Customer Name : " << customerName << endl;
	cout << "Customer Location : " << customerPostalCode << endl;

	// Step 2: Create arrays to store food items and their counts
	string tempFoodItemName;
	string uniqueItemNames[ORDER_MAX_SIZE];
	int foodItemCount[ORDER_MAX_SIZE] = { 0 };
	int uniqueItemCounter = 0;

	// Step 3: Loop through 
	for (int i = 0; i < ORDER_MAX_SIZE; i++)
	{
		// If not empty, store in temp
		if (orderedItems[i] != nullptr)
			tempFoodItemName = orderedItems[i]->getName();
		// Else go on to the next index of orderedItems
		else continue;
		// Check if the item is not unique
		int foodItemIndex = -1;
		for (int j = 0; j < uniqueItemCounter; j++)
		{
			if (uniqueItemNames[j] == tempFoodItemName)
			{
				// If found, it means that it is not unique. 
				// Break out of this forloop after indicating the index
				foodItemIndex = j;
				break;
			}
		}
		// Exiting For loop. if foodItemIndex = -1, then it means it is unique
		if (foodItemIndex == -1)
		{
			// Store the unique item inside the array
			uniqueItemNames[uniqueItemCounter] = tempFoodItemName;
			foodItemIndex = uniqueItemCounter;
			// Update counter such that it points to the next index for next unique
			uniqueItemCounter++;
		}
		foodItemCount[foodItemIndex]++;
	}

	// Iterate through unique items and item counts and print
	cout << "Food Items in Order of First Occurrence : " << endl;
	for (int k = 0; k < uniqueItemCounter; k++)
	{
		cout << foodItemCount[k] << "x " << uniqueItemNames[k] << endl;
	}
	cout << "Total Cost : $" << totalCost() << endl;
}

// Derive total cost of the order
// Iterate through items and add to total cost
double Order::totalCost()
{
	double totalCost = 0;
	for (int i = 0; i < ORDER_MAX_SIZE; i++)
	{
		if (orderedItems[i] != nullptr)
			totalCost += orderedItems[i]->getPrice();
	}
	return totalCost;
}
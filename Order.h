#pragma once
#include <string>
#include <iostream>
#include "foodItem.h"
#include "User.h"
#include "Customer.h"
#include "RestaurantStaff.h"

using namespace std;
const int ORDER_MAX_SIZE = 20;

// Forward declaration
class Customer;
class Restaurant;

class Order
{
private:
    Customer* customerPointer = nullptr;    // Stores pointer to customer rather than copying object
    Restaurant* restaurantPointer = nullptr;// Stores pointer to restaurant rather than copying object
    FoodItem* orderedItems[ORDER_MAX_SIZE]; // Stores array of pointer to food objects that is to be prepared
    string orderStatus = "In Progress";     // Stores information about the state of the order
    string customerName;                    // Stores customer name
    string restaurantName;
    int customerPostalCode;                 // Stores customer postal code
    int size = 0;                            // Stores size of the order

public:

    // Default constructor
    Order();

    // Parameterized Constructor
    Order(Customer* aCustomerPointer, Restaurant* aRestaurant);

    // Destructor
    ~Order();

    // Get ordered items || more for report generation
    // Pre : ~
    // Post: aFoodPointerArray contains all ordered item pointers
    void getOrderedItems(FoodItem* aFoodPointerArray[ORDER_MAX_SIZE]);

    // Get order status 
    // Pre : ~
    // Post: Get order status
    string getOrderStatus();

    // Get customer name
    // Pre : ~
    // Post: Get customer name
    string getCustomerName();

    // Get customer postalcode
    // Pre : ~
    // Post: Get customer postalcode
    int getCustomerPostalCode();

    // Get the size
    // Pre : ~
    // Post: Get size
    int getSize();

    // Get the Restaurant Pointer
	// Pre : ~
	// Post: Get Restaurant Pointer
    Restaurant* getRestaurantPointer();

    // Set the two main parties involved in an order, customer & restaurant
    // Pre : ~
    // Post: customer pointer and restaurant pointer are set
    void setPartyInformation(Customer* aCustomer,Restaurant* aRestaurant);

    // Set postal code of customer
	// Pre : ~
	// Post: Set customer postal code
    void setCustomerPostalCode(int aPostalCode);

    // Set name of customer
	// Pre : ~
	// Post: Set customer name
    void setCustomerName(string aName);

    // Set name of restaurant
	// Pre : ~
	// Post: Set restaurant name
    void setRestaurantName(string aName);

    // Set method for order status from restaurant
    // Pre  : ~
    // Post : order status changed to completed
    void setOrderStatusComplete();

    // checks if ordered items is full
    // Pre : ~
    // Post: Returns true if full, false otherwise
    bool isFull();

    // Add food item into orderedItems
    // Pre : foodOrderedItems must not be full
    // Post: 
    bool addFoodItem(FoodItem* aFoodItemPointer);

    // Remove food item from order
    // Pre : food item must exist within the order
    // Post : Return success or error message
    bool removeFoodItem(FoodItem* item);

    // Print all relevant order information
    // Pre : ~
    // Post: ~
    void printOrderInformation();

    // Derive total cost of the order
    // Pre : ~
    // Post: Returns total cost
	double totalCost();
};


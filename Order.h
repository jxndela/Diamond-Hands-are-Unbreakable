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

    int getSize()
    {
        return size;
    }

    Restaurant* getRestaurantPointer()
    {
        return restaurantPointer;
    }

    void setPartyInformation(Customer* aCustomer,Restaurant* aRestaurant)
    {
        customerPointer = aCustomer;
        restaurantPointer = aRestaurant;
    }

    void setCustomerPostalCode(int aPostalCode)
    {
        customerPostalCode = aPostalCode;
    }

    void setCustomerName(string aName)
    {
        customerName = aName;
    }

    void setRestaurantName(string aName)
    {
        restaurantName = aName;
    }
    // Get size of the 


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
};


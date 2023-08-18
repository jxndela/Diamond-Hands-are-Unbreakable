#pragma once
#include <iostream>
#include <string>
#include "User.h"
#include "Order.h"
#include "Restaurant.h"
#include "RestaurantArray.h"

using namespace std;

// Forward declaration
class Order;
class Restaurant;
class RestaurantArray;

// Customer class is derived from user
// This means that it inherits email + password
class Customer :  User
{
private:

    // Private attributes 
    string customerName;   // Stores customer name
    int postalCode;        // Store customer's postal code 
    Order* currentOrder = nullptr;
    int numberOfpreviousOrders = 0; 

public:

    // Default constructor 
    Customer();

    // Parameterized constructor 
    Customer(string aEmail, string aPasswordhash, string aCustomerName, int aPostalCode);

    // Destructor Override method as customer is virtual
    // Pre : ~
    // Post: Customer is deleted 
    ~Customer();

    // Get Customer Name
    // Pre : ~
    // Post: String customer name
    string getCustomerName();

    // Get Customer Name
    // Pre : ~
    // Post: INT customer postal code is returned 
    int getCustomerPostalCode();

    // Check the passwordHash of a user object
    // Pre : ~
    // Post: Returns passwordHash string
    string getPasswordHash();

    // Check the email of a user object
    // Pre : ~
    // Post: Returns email string
    string getEmail();

    // Get current order
    // Pre : ~
    // Post: Get pointer to the current order of the customer
    Order* getCurrentOrder();

    int getNumberOfPreviousOrders()
    {
        return numberOfpreviousOrders;
    };


    // Can only order from 1 restaurant
    // Generate a temporary Order Variable
    // Pre : No orders in progress
    //       We also need restaurant that you are ordering from
    //       As well as 
    // Post: Create a temporary order to store foodItems in 
    bool createNewOrder(Order* aNewOrder,RestaurantArray* aRestaurantDatabase);

    FoodItem* selectFoodItem(Order* aOrder)
    {

    }


    // Confirm the order and send it to Restaurant
    // Pre : Order is not empty
    // Post: Send the order to the Restaurant orders queue
    void confirmOrder();

    // Cancel an order 
    // Pre : There must be an existing order that is in progress
    // Post: Returns true if successful, returns false otherwise
    bool cancelOrder(Order& order);

    // set password hash
	// pre : ~
	// post : password hash is set
	void setPasswordHash(string aPasswordaHash);
    
};


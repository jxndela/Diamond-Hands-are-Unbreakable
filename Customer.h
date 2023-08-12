#pragma once
#include <iostream>
#include <string>
#include "User.h"
#include "Order.h"

using namespace std;

// Forward declaration
class Order;

// Customer class is derived from user
// This means that it inherits email + password
class Customer :  User
{
private:

    // Private attributes 
    string customerName;   // Stores customer name
    int postalCode;        // Store customer's postal code 
    Order* currentOrder = nullptr;

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
    // Post: customer name
    string getCustomerName();

    // Get Customer Name
    // Pre : ~
    // Post: customer name
    int getCustomerPostalCode();

    // Check the passwordHash of a user object
    // Pre : ~
    // Post: Returns passwordHash
    string getPasswordHash();

    // Check the email of a user object
    // Pre : ~
    // Post: Returns email
    string getEmail();

    // Generate UI For browsing Food Selection
    // Pre : ~
    // Post: Show the food selection with options to sort 
    void browseFoodSelections();

    // Generate a temporary Order Variable
    // Pre : No orders in progress 
    // Post: Create a temporary order to store foodItems in 
    void createNewOrder();

    // Confirm the order and send it to Restaurant
    // Pre : Order is not empty
    // Post: Send the order to the Restaurant orders queue
    void confirmOrder();

    // Cancel an order 
    // Pre : There must be an existing order that is in progress
    // Post: Returns true if successful, returns false otherwise
    //bool cancelOrder(Order& order);
};


#pragma once
#include <iostream>
#include <string>
#include "User.h"
#include "Restaurant.h"
#include "Order.h"

using namespace std;

// Forward Declaration
class Order;
class Restaurant;

class RestaurantStaff : User
{
private:

	Restaurant* restaurantPointer = nullptr;	// Stores the branch which the staff works at

public:

	// Constructor
	RestaurantStaff();

	// Parameterized Constructor
	RestaurantStaff(string aEmail, string aPasswordhash, Restaurant* aRestaurantPointer);

	// Destructor
	~RestaurantStaff();

	// View all active orders 
	// Pre : ~
	// Post: Return UI showing all the active orders
	void viewAllOrders();

	// View specific order information
	// Pre : ~
	// Post: Return UI showing customer info and food items
	void viewOrderAndCustomerInfo(Order aOrder);

	// Update the order status 
	// Pre : Order must exist
	// Post: Success or failure 
	void updateOrderStatus(Order aOrder);

	// Update the food item attributes
	// Pre : Food Item must exist
	// Post: Success or failure 
	void updateFoodItem(FoodItem foodItem);

	// Check the email of a user object
	// Pre : ~
	// Post: Returns email
	string getEmail();

	// Check the passwordHash of a user object
	// Pre : ~
	// Post: Returns passwordHash
	string getPasswordHash();

	// set password hash
	// pre : ~
	// post : password hash is set
	void setPasswordHash(string aPasswordHash);

	// Generate Report
	// Pre : Must have completed orders in a given time period
	// Post: Shows monthly report of total earnings and statistics.
	void generateReport();

};
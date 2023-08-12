#pragma once
#include <iostream>
#include <string>
#include "User.h"

using namespace std;

class RestaurantStaff : User
{
private:
	string branchName;	// Stores the branch which the staff works at

public:

	// Constructor
	RestaurantStaff();

	// Parameterized Constructor
	RestaurantStaff(string aBranchName);

	// Destructor
	~RestaurantStaff();

	// View all active orders 
	// Pre : ~
	// Post: Return UI showing all the active orders
	void viewAllOrders();

	// View specific order information
	// Pre : ~
	// Post: Return UI showing customer info and food items
	void viewOrderAndCustomerInfo(string aOrder);

	// Update the order status 
	// Pre : Order must exist
	// Post: Success or failure 
	void updateOrderStatus();

	// Update the food item attributes
	// Pre : Food Item must exist
	// Post: Success or failure 
	void updateFoodItem();

	// Generate Report
	// Pre : Must have completed orders in a given time period
	// Post: Shows monthly report of total earnings and statistics.
	void generateReport();

};


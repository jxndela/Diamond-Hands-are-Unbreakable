// DSA Diamond Hands Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Header Guard
#pragma once

// Include allowed libraries
#include <iostream>
#include <string>
#include <fstream>	// For reading writing files
#include <sstream>	

// Include all the header files
#include "User.h"
#include "CustomerDictionary.h"
#include "Customer.h"
#include "StaffDictionary.h"
#include "RestaurantStaff.h"
#include "Restaurant.h"
#include "FoodItem.h"
#include "FoodItemAVL.h"
#include "Order.h"
#include "OrderQueue.h"
#include "RestaurantArray.h"

using namespace std;


int main()
{
	// Initialize the Restaurant database, automatically creates fooditems previously stored
	// Constructor automatically reads save file
	RestaurantArray restaurantDatabase;
	/////readRestaurantFile(restaurantDatabase, numberOfRestaurants);
	// Initalize staff database
	StaffDictionary staffDatabase;
	staffDatabase.loadFromFile(restaurantDatabase.GetAllRestaurant(), restaurantDatabase.getNumberOfRestaurants());
	// Initaliaze user database
	CustomerDictionary userDatabase;
	// Set-up and exit condition for UI
	Customer* customerPointer = nullptr;
	RestaurantStaff* staffPointer = nullptr;
	bool customerLoggedIn = false;
	bool staffLoggedIn = false;
	string staffEmail;



	// User presented with two choices to log in or register
	while (customerLoggedIn == false && staffLoggedIn == false)
	{
		// Display message and prompt for choice
		cout << " _  _  _ _______        _______  _____  _______ _______" << endl;
		cout << " |  |  | |______ |      |       |     | |  |  | |______" << endl;
		cout << " |__|__| |______ |_____ |_____  |_____| |  |  | |______" << endl;
		cout << endl;
		cout << "1. User Login" << endl;
		cout << "2. User Register" << endl;
		cout << "3. Staff Login" << endl;
		cout << "4. Staff Register" << endl;
		cout << "Your choice? (1 - 4) : ";
		int loginChoice;
		cin >> loginChoice;
		switch (loginChoice)
		{
		case 1:	// 1. User Login
			cout << "         _____   ______ _____ __   _" << endl;
			cout << " |      |     | |  ____   |   | |  |" << endl;
			cout << " |_____ |_____| |_____| __|__ |  |_|" << endl;
			cout << endl;
			cout << "Customer Login" << endl;

			// If successful, break out of while loop
			if (userDatabase.customerLogin(customerPointer))
			{
				customerLoggedIn = true;
				break;
			}
			break;
		case 2:	// 2. User Register
			cout << "  ______ _______  ______ _____ _______ _______ _______  ______" << endl;
			cout << " |_____/ |______ |  ____   |   |______    |    |______ |_____/" << endl;
			cout << " |    L_ |______ |_____| __|__ ______|    |    |______ |    L_" << endl;
			cout << endl;
			cout << "Customer Registration" << endl;
			// If successful, continue the while loop. 
			if (userDatabase.registerCustomerAccount())
			{
				continue;
			}
			break;
		case 3:	// 3. Staff Login
			cout << "         _____   ______ _____ __   _" << endl;
			cout << " |      |     | |  ____   |   | |  |" << endl;
			cout << " |_____ |_____| |_____| __|__ |  |_|" << endl;
			cout << endl;
			cout << "Restaurant Staff Login" << endl;
			// If successful break out of while loop
			if (staffDatabase.stafflogin(staffPointer))
			{
				staffLoggedIn = true;
				break;
			}
			break;
		case 4:	// 4. Staff Register
			cout << "  ______ _______  ______ _____ _______ _______ _______  ______" << endl;
			cout << " |_____/ |______ |  ____   |   |______    |    |______ |_____/" << endl;
			cout << " |    L_ |______ |_____| __|__ ______|    |    |______ |    L_" << endl;
			cout << endl;
			// Restaurant staff registration
			cout << "Restaurant Staff Registration" << endl;
			if (staffDatabase.registerStaffAccount(restaurantDatabase))
			{
				continue;
			}
			break;
		default:// Input validation
			cout << "Invalid input. Please enter a valid option." << endl;
			cout << "-------------------------------------------" << endl;
			cin.clear();                 // Clear the failed state
			cin.ignore(INT_MAX, '\n');  
			continue;
		}
	}
	// If it is the customer who is logged in, show options only available to customer
	while(customerLoggedIn)
	{
		//Present interface for the user
		cout << "====================================================" << endl;
		cout << "Welcome Back" << endl;
		cout << "What would you like to do?" << endl;
		cout << "1. Create new order" << endl;
		cout << "2. Check order" << endl;
		cout << "3. Cancel Order" << endl;
		cout << "4. Log out" << endl;
		cout << "Your choice ? ";
		int loginChoice;
		cin >> loginChoice;
		switch (loginChoice)
		{
		case 1:
			// Create order
			cout << "____ ____ ____ ____ ___ ____    _  _ ____ _ _ _    ____ ____ ___  ____ ____ " << endl;
			cout << "|    |__/ |___ |__|  |  |___    || | |___ | | |    |  | |__/ |  | |___ |__/ " << endl;
			cout << "|___ |  | |___ |  |  |  |___    | || |___ |_|_|    |__| |  | |__/ |___ |  | " << endl;
			cout << "                                                                            " << endl;  
		case 2:
			// Check current in progress order
		case 3:
			// Cancel in progress order
		case 4:
			// Log out
		default: // Else show an error
			cout << "Invalid input. Please enter a valid option." << endl;
			cout << "-------------------------------------------" << endl;
			cin.clear();                 // Clear the failed state
			cin.ignore(INT_MAX, '\n');
			continue;
		}
	}
	while(staffLoggedIn)
	{
		
	}
}
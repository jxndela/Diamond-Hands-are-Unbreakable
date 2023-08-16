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

	// Display message and prompt for choice
	cout << " _  _  _ _______        _______  _____  _______ _______" << endl;
	cout << " |  |  | |______ |      |       |     | |  |  | |______" << endl;
	cout << " |__|__| |______ |_____ |_____  |_____| |  |  | |______" << endl;
	cout << endl;

	// User presented with two choices to log in or register
	while (customerLoggedIn == false && staffLoggedIn == false)
	{
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
		default:// Input validation
			cout << "Invalid choice, please enter a valid option" << endl;
			continue;
		}
	}

	//if (customerLoggedIn)
	//{
	//	// Present interface for the user
	//	cout << "====================================================" << endl;
	//	cout << "Welcome Back" << endl;
	//	cout << "What would you like to do?" << endl;
	//	cout << "1. Create new order\n2. Check order\n3. Cancel Order\n4. Log out" << endl;
	//	// While loop for prompt
	//	bool validCustomerResponse = false;
	//	string customerInput;
	//	while (!validCustomerResponse)
	//	{
	//		cout << "Your choice ? : ";
	//		cin >> customerInput;
	//		// 3 options
	//		if (customerInput == "1")
	//		{
	//			cout << "____ ____ ____ ____ ___ ____    _  _ ____ _ _ _    ____ ____ ___  ____ ____ " << endl;
	//			cout << "|    |__/ |___ |__|  |  |___    || | |___ | | |    |  | |__/ |  | |___ |__/ " << endl;
	//			cout << "|___ |  | |___ |  |  |  |___    | || |___ |_|_|    |__| |  | |__/ |___ |  | " << endl;
	//			cout << "                                                                            " << endl;  
	//			
	//			// Display UI for restaurants and their menus
	//			//////printRestaurants(restaurantDatabase, numberOfRestaurants);
	//			// Create the temporary order
	//			Order* temporaryOrder = nullptr;
	//			// Create an array of valid inputs
	//			// Start at index zero, but value start at 1
	//			string restaurantChoices[MAX_RESTAURANTS];
	//			for (int i = 0; i < restaurantDatabase.getNumberOfRestaurants(); i++)
	//			{
	//				restaurantChoices[i] = to_string(i + 1);
	//			}
	//			// Create exit condition
	//			bool validRestaurantChoice = false;
	//			string restaurantChoice; 
	//			Restaurant* restaurantChosen = nullptr; // Initialize the pointer to nullptr
	//			// This is the one that is ultimately selected
	//			// Prompt user to select restaurant to order from
	//			while (!validRestaurantChoice)
	//			{
	//				cout << "which restaurant would you like to order from? : ";
	//				cin >> restaurantChoice;
	//				bool found = false;
	//				// If it is not valid 

	//				for (int i = 0; i < restaurantDatabase.getNumberOfRestaurants(); i++)
	//				{
	//					if (restaurantChoice == restaurantChoices[i])
	//					{
	//						validRestaurantChoice = true;
	//						restaurantChosen = &(restaurantDatabase.GetAllRestaurant())[stoi(restaurantChoice) - 1];
	//						temporaryOrder = customer.createNewOrder(restaurantChosen);
	//						found = true;
	//						break;
	//					}
	//				}
	//				// Exit out of for loop
	//				if (found)
	//				{
	//					cout << "Creating an empty order form..." << endl;
	//					break;
	//				}
	//				else
	//					cout << "Please enter appropriate integer corresponding to restaurant" << endl;
	//				
	//			}
	//			// Broke out of while loop - Order is created
	//			// Show that specific restaurant menu to prompt user
	//			restaurantChosen->printMenu();
	//			cout << "What would you like to order?" << endl;
	//			// 
	//			bool isOrderConfirmed = false;

	//			// While not confirmed and not full, allow adding of food items
	//			while (!isOrderConfirmed && !temporaryOrder->isFull())
	//			{
	//				// temp
	//				FoodItem* foodItemPointer = nullptr;
	//				string foodItemName;
	//				// prompt user
	//				cout << "Type the exact name of the food you would like to order" << endl;
	//				cin >> foodItemName;

	//				// search in the menu if it exists
	//				foodItemPointer = restaurantChosen->getRestaurantMenuPointer()->searchNode(foodItemName);

	//				if (foodItemPointer == nullptr)
	//				{
	//					cout << "Food item does not exist, please try again";
	//				}
	//				else
	//				{
	//					cout << foodItemPointer->getName() << " has been added to your order.";
	//				}

	//				//if (temporaryOrder.)
	//			}
	//		}
	//		else if (customerInput == "2")
	//		{
	//			cout << "____ _  _ ____ ____ _  _    ____ ____ ___  ____ ____ " << endl;
	//			cout << "|    |__| |___ |    |_/     |  | |__/ |  | |___ |__/ " << endl;
	//			cout << "|___ |  | |___ |___ | |_    |__| |  | |__/ |___ |  | " << endl;
	//			cout <<                                                      "" << endl;

	//		}
	//		else if (customerInput == "3")
	//		{
	//			cout << "____ ____ _  _ ____ ____ _       ____ ____ ___  ____ ____ " << endl;
	//			cout << "|    |__| || | |    |___ |       |  | |__/ |  | |___ |__/ " << endl;
	//			cout << "|___ |  | | || |___ |___ |___    |__| |  | |__/ |___ |  | " << endl;
	//			cout << "                                                          " << endl;
	//		}
	//		else
	//		{
	//			cout << "Invalid input, please try select appropriate number" << endl;
	//			continue;
	//		}
	//	}
	//	// Break out of user options menu
	//}
	//if (restaurantStaffLoggedIn)
	//{
	//	restaurantStaff = staffDatabase.search(staffEmail);
	//	
	//	// Present interface for the user
	//	cout << "====================================================" << endl;
	//	cout << "Welcome Back, " << restaurantStaff->getRestaurantName() << endl;
	//	while (true)
	//	{
	//		cout << "1. View Incoming Orders\n2. View customer information of latest order\n3. Update Order\n4. Generate Report\n5. Add food item To Menu\n6. Edit food item\n7. View Menu" << endl;
	//		cout << "What would you like to do? ";
	//		// Get input from user
	//		string staffInput;
	//		cin >> staffInput;

	//		// If input is 1
	//		if (staffInput == "1")
	//		{
	//			// Print out all the orders
	//			restaurantStaff->viewAllOrders();
	//		}
	//		else if (staffInput == "2")
	//		{
	//			// Print out the latest order
	//			
	//		}
	//		else if (staffInput == "3")
	//		{
	//			// Update order

	//		}
	//		else if (staffInput == "4")
	//		{
	//			// Generate report
	//		}
	//		else if (staffInput == "5")
	//		{
	//			// Add food item to menu
	//			restaurantStaff->addFoodItem(restaurantStaff);
	//			// Save changes to the restaurant.txt file after adding the food item
	//			//writeRestaurantFile(restaurantDatabase, numberOfRestaurants);
	//		}
	//		else if (staffInput == "6")
	//		{
	//			// Call the editFoodItems function
	//			editFoodItems(restaurantStaff);
	//			// Save changes to the restaurant.txt file after updating the food item
	//			//writeRestaurantFile(restaurantDatabase, numberOfRestaurants);

	//			
	//		}
	//		else if (staffInput == "7")
	//		{
	//			// View menu
	//			restaurantStaff->getRestaurantPointer()->printMenuAll();
	//		}
	//		else
	//		{
	//			cout << "Invalid input, please try select appropriate number" << endl;
	//		}
	//	}
	//}
}
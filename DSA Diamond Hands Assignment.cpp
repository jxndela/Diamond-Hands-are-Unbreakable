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


using namespace std;

int main()
{
	// Initialize the Restaurant database, automatically creates fooditems previously stored
	// Constructor automatically reads save file
	RestaurantArray restaurantDatabase;
	/////readRestaurantFile(restaurantDatabase, numberOfRestaurants);
	// Initalize staff database
	StaffDictionary staffDatabase;
	staffDatabase.loadFromFile(&restaurantDatabase);
	// Initaliaze user database
	CustomerDictionary userDatabase;
	// Set-up and exit condition for UI
	Customer* customerPointer = nullptr;
	RestaurantStaff* staffPointer = nullptr;
	bool customerLoggedIn = false;
	bool staffLoggedIn = false;
	string staffEmail;


	while(true)
	{
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
			{
				cout << "         _____   ______ _____ __   _" << endl;
				cout << " |      |     | |  ____   |   | |  |" << endl;
				cout << " |_____ |_____| |_____| __|__ |  |_|" << endl;
				cout << endl;
				cout << "Customer Login" << endl;

				// If successful, break out of while loop
				if (userDatabase.customerLogin(customerPointer))
				{
					customerLoggedIn = true;
					cout << "customer pointer " << customerPointer << endl;
					break;
				}
				break;
			}

			case 2:	// 2. User Register
			{
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
			}
			case 3:	// 3. Staff Login
			{
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
			}
			case 4:	// 4. Staff Register
			{
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
			}
			default:// Input validation
				cout << "Invalid input. Please enter a valid option." << endl;
				cout << "-------------------------------------------" << endl;
				cin.clear();                 // Clear the failed state
				cin.ignore(INT_MAX, '\n');
				continue;
			}
		}
		// If it is the customer who is logged in, show options only available to customer
		while (customerLoggedIn)
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
			case 1: // Create order
			{
				cout << "____ ____ ____ ____ ___ ____    _  _ ____ _ _ _    ____ ____ ___  ____ ____ " << endl;
				cout << "|    |__/ |___ |__|  |  |___    || | |___ | | |    |  | |__/ |  | |___ |__/ " << endl;
				cout << "|___ |  | |___ |  |  |  |___    | || |___ |_|_|    |__| |  | |__/ |___ |  | " << endl;
				cout << "                                                                            " << endl;
				if (customerPointer->getCurrentOrder() != nullptr)
				{
					cout << "You can only have 1 order at a time. " << endl;
					cout << "Check your order status and confirm its arrival before starting new order." << endl;
				}
				Order* newOrder = new Order;
				// If successfully created return true
				if (customerPointer->createNewOrder(newOrder, &restaurantDatabase))
					cout << "Order Successfully created" << endl;
				else
					break;
				// Add items into basket
				Restaurant selectedRestaurant = *newOrder->getRestaurantPointer();
				FoodItemAVL selectedMenu = *selectedRestaurant.getRestaurantMenuPointer();
				string customerFoodChoice;
				// Print menu of restaurant
				selectedRestaurant.printMenu();
				bool isFirstItemSelected = false;
				while (true)
				{
					// Prompt user for input
					cout << "Please enter the exact name of dish you wish to order (Type 'exit' to exit) : ";
					getline(cin, customerFoodChoice);
					// Check if input matches any of the name
					if (customerFoodChoice == "exit")
						break;
					// Create temporary pointer to store
					FoodItem* tempFoodItem = selectedMenu.searchNode(customerFoodChoice);
					if (tempFoodItem == nullptr)
					{
						cout << "Please enter a valid food item name which you wish to order." << endl;
						cout << "------------------------------------------------------------" << endl;
						continue;
					}
					// Else it is successful it finding a food item, add into the order
					if (newOrder->addFoodItem(tempFoodItem) == false)
					{
						cout << "Addition of food item unsuccessful. Something went wrong" << endl;
						cout << "--------------------------------------------------------" << endl;
					}
					// Print success message
					cout << "Successfully added " << tempFoodItem->getName() << " into the order." << endl;
				}
				// confirm the order and send over to the order queue
				char customerResponse;
				while (true)
				{
					newOrder->printOrderInformation();
					cout << "Would you like to confirm your order? (Order will be cancelled otherwise) Y/N : ";
					cin >> customerResponse;
					if (tolower(customerResponse) == 'n')
					{
						cout << "Order cancelled" << endl;
						break;
					}
					if (tolower(customerResponse) == 'y')
					{
						cout << "Order confirmed" << endl;
						break;
					}
					cout << "Invalid response, please try again.";
					cout << "-----------------------------------";
				}
				if (customerResponse == 'n') break;
				if (customerResponse == 'y')
				{
					selectedRestaurant.getIncomingOrder()->enqueue(newOrder);
					cout << "Order has been sent to the restaurant" << endl;
					break;
				}
			}
			case 2: // Check current in progress order
			{
				if (customerPointer->getCurrentOrder() == nullptr)
				{
					cout << "No Current Orders ongoing" << endl;
					continue;
				}
				customerPointer->getCurrentOrder()->printOrderInformation();
				continue;
			}
			case 3: // Cancel in progress order
			{
				if (customerPointer->getCurrentOrder() == nullptr)
				{
					cout << "No orders to cancel" << endl;
					continue;
				}
				// Access the order queue of current order
				Order* currentOrder = customerPointer->getCurrentOrder();
				OrderQueue* restaurantQueue = currentOrder->getRestaurantPointer()->getIncomingOrder();
				// Else not found, dequeue it and enqueue it into the temp queue
				OrderNode* currentNode = restaurantQueue->getFrontOrderNode();
				OrderQueue* tempQueue = new OrderQueue;
				while (currentNode != nullptr)
				{
					// Case 1 found
					if (currentNode->orderPointer->getCustomerName() == currentOrder->getCustomerName())
					{
						cout << "Found" << endl;
						restaurantQueue->dequeue(); // cancel the order
						// push the rest of the orders into the temporary queue
						currentNode = currentNode->next;
						while (currentNode != nullptr)
						{
							Order* transferPointer = currentNode->orderPointer;
							tempQueue->enqueue(transferPointer);
							currentNode = currentNode->next;
							restaurantQueue->dequeue();
						}
						// Push everything back to the original queue, but now without customer order
						currentNode = tempQueue->getFrontOrderNode();
						while (currentNode != nullptr)
						{
							Order* transferPointer = currentNode->orderPointer;
							restaurantQueue->enqueue(transferPointer);
							currentNode = currentNode->next;
							tempQueue->dequeue();
						}
						delete tempQueue;
						break;
					}
					// Case 2 not found
					Order* tempOrderPointer = currentNode->orderPointer;
					tempQueue->enqueue(tempOrderPointer);
					currentNode = currentNode->next;
					restaurantQueue->dequeue();
				}
				// Set current order to none 
				customerPointer->removeCurrentOrder();
				// no. of previous orders
			}
			case 4: // Log out
			{
				cout << "Case 4" << endl;
				customerPointer = nullptr;
				customerLoggedIn = false;
				break;
			}
			default: // Else show an error
				cout << "Invalid input. Please enter a valid option." << endl;
				cout << "-------------------------------------------" << endl;
				cin.clear();                 // Clear the failed state
				cin.ignore(INT_MAX, '\n');
				continue;
			}
		}
		// If it is the staff who is logged in, show options only available to staff
		while (staffLoggedIn)
		{
			// hello where is staff function
			// 
			// this is hardcoded as fuck. but to show that it works.
			//cout << "gamer girl bath water" << endl;
			//RestaurantStaff* test = staffDatabase.search("on@gmail.com");
			//cout << test->getRestaurantPointer()->getRestaurantName() << endl;
			//break;

			cout << "====================================================" << endl;
			cout << "Welcome Back, " << staffPointer->getRestaurantPointer()->getRestaurantName() << endl;
			cout << "What would you like to do?" << endl;
			cout << "1. View All Orders" << endl;
			cout << "2. Edit Orders" << endl;
			cout << "3. View Menu" << endl;
			cout << "4. Add Food Item" << endl;
			cout << "5. Update Food Item" << endl;
			cout << "0. Logout" << endl;
			cout << "Your choice ? ";
			int loginChoice;
			cin >> loginChoice;
			switch (loginChoice)
			{
			case 1: // View All Orders
			{
				staffPointer->viewAllOrders();
				break;
			}

			case 2: // Edit Orders
			{
				cout << "i'm gna kms please dont try to edit orders yet" << endl;
				break;
			}

			case 3: // View Menu
			{
				staffPointer->getRestaurantPointer()->getRestaurantMenuPointer()->printAllInOrder();
				break;
			}

			case 4: // Add Food Item
			{
				staffPointer->addFoodItem();
				break;
			}

			case 5: // Update Food Item
			{
				//FoodItem* foodItemPointer = nullptr;
				staffPointer->updateFoodItem();
				break;
			}

			case 0: // Log out
			{
				staffPointer = nullptr;
				staffLoggedIn = false;
				break;
			}
			default: // Else show an error
				cout << "Invalid input. Please enter a valid option." << endl;
				cout << "-------------------------------------------" << endl;
				cin.clear();                 // Clear the failed state
				cin.ignore(INT_MAX, '\n');
				continue;
			}
		}
	}

	

}
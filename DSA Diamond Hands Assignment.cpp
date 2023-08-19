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
const int MAX_FOOD_ITEMS = 1000;

// Make a function that adds all the restaurant food item pointer the food item array
int addAllFoodItems(FoodItem* aFoodItemArray[], RestaurantArray& aRestaurantDatabase)
{
	int currentIndex = 0;
	// Iterate through all the restaurants
	for (int i = 0; i < aRestaurantDatabase.getNumberOfRestaurants(); i++)
	{
		Restaurant* restaurantPointer = aRestaurantDatabase.getRestaurant(i);
		FoodItemAVL* menuPointer = restaurantPointer->getRestaurantMenuPointer();
		//Call recursive function
		menuPointer->addFoodIntoArray(aFoodItemArray, currentIndex);
	}
	return currentIndex;
}

// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(FoodItem* array[], int const left, int const mid, int const right, string const filter)
{
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	// Create temp fooditem pointer array and asign pointers called left array and right array
	FoodItem** leftArray = new FoodItem*[subArrayOne];
	FoodItem** rightArray = new FoodItem*[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
	int indexOfMergedArray = left;

	if (filter == "alpha")
	{
		// Merge the temp arrays back into array[left..right]
		while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
		{
			// If item in left array is less than item in right array
			if (leftArray[indexOfSubArrayOne]->getName() <= rightArray[indexOfSubArrayTwo]->getName())
			{
				array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
				indexOfSubArrayOne++;
			}
			else // Else the item in left array is more than right array
			{
				array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
				indexOfSubArrayTwo++;
			}
			indexOfMergedArray++;
		}
	}
	if (filter == "price")
	{
		// Merge the temp arrays back into array[left..right]
		while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
		{
			// If item in left array is less than item in right array
			if (leftArray[indexOfSubArrayOne]->getPrice() <= rightArray[indexOfSubArrayTwo]->getPrice())
			{
				array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
				indexOfSubArrayOne++;
			}
			else // Else the item in left array is more than right array
			{
				array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
				indexOfSubArrayTwo++;
			}
			indexOfMergedArray++;
		}
	}
	if (filter == "category")
	{
		// Merge the temp arrays back into array[left..right]
		while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
			// If item in left array is less than or equal to item in right array
			if (leftArray[indexOfSubArrayOne]->getCategory().compare(rightArray[indexOfSubArrayTwo]->getCategory()) <= 0) 
			{
				array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
				indexOfSubArrayOne++;
			}
			else // Else the item in left array is more than right array
			{
				array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
				indexOfSubArrayTwo++;
			}
			indexOfMergedArray++;
		}
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) 
	{
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) 
	{
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

void mergeSort(FoodItem* array[], int const begin, int const end, string const filter)
{
	// base case.
	if (begin >= end)
		return;

	// Idea is to break down the pointer list into singular comparisons
	// Then reconstruct after comparisons are finsihed
	int mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid, filter); // For sub array 1
	mergeSort(array, mid + 1, end, filter); // For sub array 2
	merge(array, begin, mid, end, filter);
}



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

	// Store pre-sorted items
	FoodItem* foodItemsUnsorted[MAX_FOOD_ITEMS];
	int numberOfAllFood = addAllFoodItems(foodItemsUnsorted, restaurantDatabase);
	
	// Pre Sort the items (Alphabetically)
	mergeSort(foodItemsUnsorted, 0, numberOfAllFood - 1, "alpha");
	FoodItem* foodItemSortedAlpha[MAX_FOOD_ITEMS];
	for (int i = 0; i < numberOfAllFood; i++)
	{
		foodItemSortedAlpha[i] = foodItemsUnsorted[i];
	}
	// Pre Sort the items (Price)
	mergeSort(foodItemsUnsorted, 0, numberOfAllFood - 1, "price");
	FoodItem* foodItemSortedPrice[MAX_FOOD_ITEMS];
	for (int i = 0; i < numberOfAllFood; i++)
	{
		foodItemSortedPrice[i] = foodItemsUnsorted[i];
	}
	// Pre Sort the items (Category)
	mergeSort(foodItemsUnsorted, 0, numberOfAllFood - 1, "category");
	FoodItem* foodItemSortedCategory[MAX_FOOD_ITEMS];
	for (int i = 0; i < numberOfAllFood; i++)
	{
		foodItemSortedCategory[i] = foodItemsUnsorted[i];
	}


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
				std::cin.clear();                 // Clear the failed state
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
			cout << "5. View all food" << endl;
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
				// Check if there are existing orders
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
						delete newOrder;
						break;
					}
					if (tolower(customerResponse) == 'y' && newOrder->getSize() > 0)
					{
						selectedRestaurant.getIncomingOrder()->enqueue(newOrder);
						cout << "Order is confirmed and has been sent to the restaurant" << endl;
						customerPointer->setCurrentOrder(newOrder);
						customerPointer->confirmOrder();
						break;
					}
					if (tolower(customerResponse) == 'y' && newOrder->getSize() == 0)
					{
						cout << "Empty order cannot be submitted, it will now be voided." << endl;
						delete newOrder;
						break;
					}
					cout << "Invalid response, please try again.";
					cout << "-----------------------------------";
				}
			}
			case 2: // Check current in progress order
			{
				if (customerPointer->getCurrentOrder() == nullptr)
				{
					cout << "No Current Orders ongoing" << endl;
					continue;
				}
					if (customerPointer->getCurrentOrder()->getOrderStatus() == "Completed")
					{
						bool isOrderConfirmed = false;
						customerPointer->getCurrentOrder()->printOrderInformation();
						while (!isOrderConfirmed)
						{
							char confirmOrderReceived;
							cout << "Confirm that order is received ? (Y/N) : ";
							cin >> confirmOrderReceived;
							if (tolower(confirmOrderReceived) == 'n')
							{
								cout << "Order has not been delivered yet, returning to menu." << endl;
								break;
							}
							if (tolower(confirmOrderReceived) == 'y')
							{
								cout << "Order has been received." << endl;
								// INSERT POINTS???????????????????????
								customerPointer->getCurrentOrder()->getRestaurantPointer()->getIncomingOrder()->dequeue();
								customerPointer->setCurrentOrder(nullptr);
								break;
							}
						}
						continue;
					}
				customerPointer->getCurrentOrder()->printOrderInformation();
				continue;
			}
			case 3: // Cancel in progress order
				{
					// If no Orders we just return no orders to cancel
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
							cout << "Order found and dequeued" << endl;
							restaurantQueue->dequeue(); // cancel the order
							// Check if any items left in the queue
							if (restaurantQueue->getFrontOrderNode() != nullptr)
							{
								// Make current node the front node of the restaurant queue
								currentNode = restaurantQueue->getFrontOrderNode();
								// Push all the leftover nodes into the tempQueue
								while (currentNode != nullptr)
								{
									tempQueue->enqueue(currentNode->orderPointer);
									currentNode = currentNode->next;
									restaurantQueue->dequeue();
								}
							}
							// Push everything back to the original queue, but now without customer order
							currentNode = tempQueue->getFrontOrderNode();
							while (currentNode != nullptr)
							{
								restaurantQueue->enqueue(currentNode->orderPointer);
								currentNode = currentNode->next;
								tempQueue->dequeue();
							}
							break;
						}
						// Case 2 not found, push the current order pointer into the temp queue
						tempQueue->enqueue(currentNode->orderPointer);
						currentNode = currentNode->next;
						restaurantQueue->dequeue();
					}
					// Set current order to none 
					customerPointer->removeCurrentOrder();
				}
			case 4: // Log out
			{
				cout << "Case 4" << endl;
				customerPointer = nullptr;
				customerLoggedIn = false;
				break;
			}
			case 5: // View All food items
			{
				bool isDoneViewing = false;
				string customerViewChoice;
				FoodItem** foodItemViewMode = foodItemSortedAlpha;	// Default view is alphabetical order
				while(!isDoneViewing)
				{
					for (int i = 0; i < numberOfAllFood; i++)
					{
						// Print UI for each other
						cout << i + 1 << ". " << "Name: " << foodItemViewMode[i]->getName() << endl
							<< "   Price: " << foodItemViewMode[i]->getPrice() << endl
							<< "   Category: " << foodItemViewMode[i]->getCategory() << endl
							<< "   Description: " << foodItemViewMode[i]->getFoodDescription() << endl
							<< "----------------------------------------" << endl;
					}
					// Prompt customer for response
					cout << "1. Return back to menu" << endl;
					cout << "2. Sort by Alphabetical Order" << endl;
					cout << "3. Sort by Price" << endl;
					cout << "4. Sort by Category" << endl;
					cout << "5. Search for item" << endl;
					cout << "Your choice ? : ";
					getline(cin, customerViewChoice);
					if (customerViewChoice == "1") // Return back to menu
						break;
					if (customerViewChoice == "2")	// Alphabetical order
					{
						cout << "Now sorting by alphabetical order" << endl;
						foodItemViewMode = foodItemSortedAlpha;
						continue;
					}
					if (customerViewChoice == "3")	// Price order
					{
						cout << "Now sorting by price in ascending order" << endl;
						foodItemViewMode = foodItemSortedPrice;
						continue;
					}
					if (customerViewChoice == "4")	// Category order
					{
						cout << "Now sorting by category alphabetically" << endl;
						foodItemViewMode = foodItemSortedCategory;
						continue;
					}
					if (customerViewChoice == "5")	// Search to find out where the food item is from
					{
						// Prompt user to search
						FoodItem* itemSearched = nullptr;
						string customerSearch;	
						cout << "Please enter the exact name of dish you wish to find more info (Type 'exit' to exit) : ";
						getline(cin, customerSearch);
						// Find which item has been searched for
						for (int i = 0; i < numberOfAllFood; i++)
						{
							if (customerSearch == foodItemsUnsorted[i]->getName())
							{
								// if the name mathces, item searched is stored
								itemSearched = foodItemsUnsorted[i];
							}
						}
						// no match = nullptr
						if (itemSearched == nullptr)
						{
							cout << "Invalid item name, please try again." << endl;
							continue;
						}
						// Find more info
						for (int i = 0; i < restaurantDatabase.getNumberOfRestaurants();i++)
						{
							// If found inside the restaurant, show the restaurant information
							if (itemSearched ==
								restaurantDatabase.getRestaurant(i)->getRestaurantMenuPointer()->searchNode(customerSearch))
							{
								// Display infomartion about where to order it from
								cout << itemSearched->getName() << " is an item found in "
									<< restaurantDatabase.getRestaurant(i)->getRestaurantName() << endl;
								isDoneViewing = true;
								break;
							}
						}
						continue;
					}
					cout << "Invalid input. Please enter a valid option." << endl;
					cout << "-------------------------------------------" << endl;
					continue;
				}
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

			//cout << "gamer girl bath water" << endl;
			cout << "====================================================" << endl;
			cout << "Welcome Back, " << staffPointer->getRestaurantName() << endl;
			cout << "What would you like to do?" << endl;
			cout << "1. View All Orders" << endl;
			cout << "2. Update Order Status" << endl;
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
			case 2: // update Order Status
			{
				Order* aOrder = staffPointer->getRestaurantPointer()->getIncomingOrder()->getFrontOrderNode()->orderPointer;
				staffPointer->updateOrderStatus(*aOrder);
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
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




// INPUT HELPERS
string hashPassword(const string& aUnhashedPassword)
{
	// TEMPORARY HASH FUNCTION
	int sum = 0;
	for (int i = 0; i < aUnhashedPassword.length(); i++)
	{
		sum += aUnhashedPassword[i];
	}
	string hashedPassword = to_string((sum % CUSTOMER_MAX_SIZE));
	return hashedPassword;
}

// Simple validator, however it is unable to accept domain name aside from .com
bool isValidEmail(string& email)
{
	if (email.empty())
		return false;

	// Find locations of @ and . symbol
	const size_t atIndex = email.find('@');
	const size_t dotIndex = email.rfind('.');

	// Check if '@' and '.' are both present and in the correct order
	// if index is -1, means not present
	if (atIndex == -1 || dotIndex == -1 || atIndex > dotIndex) {
		return false;
	}

	// Check for ".com" domain nane
	string const domain = email.substr(dotIndex + 1);
	if (domain != "com") {
		return false;
	}

	// Check for alphanumeric characters before '@' index 0 to atIndex
	string const localPart = email.substr(0, atIndex);
	// Iterate through the characters
	for (char  c : localPart) {
		if (!isalnum(c)) {
			return false;
		}
	}
	return true;
}

// Check if valid postal code
// Postal Codes in SG are all 6 digits long , any digit is OK
bool isValidPostalCode(const string& input)
{
	if (input.length() != 6) {
		return false;
	}
	for (const char c : input) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

// Function to get user email input
string getUserEmailInput()
{
	bool validInput = false;
	string userInputEmail;
	while (!validInput)
	{
		cout << "Please enter your email : ";
		cin >> userInputEmail;

		// Check for formatting and further validation
		// If invalid email
		if (!isValidEmail(userInputEmail))
		{
			cout << "Must include '@' as well as '.com' in correct order" << endl;
			cout << "Invalid email address, please try again " << endl;
			continue;
		}
		// Else, it means it passed validation req
		return userInputEmail;
	}
	// ensure all control paths will return a value
	return {};
}

// Similar function but for postal code
int getValidatedInt()
{
	bool validInput = false;
	string userInputPostalCode;
	while (!validInput)
	{
		cout << "Please enter your Postal code : ";
		cin >> userInputPostalCode;
		// Check if valid postal code
		if (!isValidPostalCode(userInputPostalCode))
		{
			cout << "Invalid postal code. Postal code should 6 Digits long, please try again" << endl;
			continue;
		}
		// Else passes validations
		return stoi(userInputPostalCode);
	}
	return 0;
}

//// Read the restaurant file
//void readRestaurantFile(Restaurant restaurantDatabase[], int& numberOfRestaurants)
//{
//
//	ifstream file("restaurant.txt");
//	std::string line;
//
//	while (getline(file, line) && numberOfRestaurants < MAX_RESTAURANTS)
//	{
//		// store the first line
//		istringstream iss(line);
//		string firstWord; 
//		// store first word
//		iss >> firstWord;
//
//		if (firstWord == "Restaurant")
//		{
//			// Create temp storers
//			string restaurantName;
//			int postalCode;
//			// After identifier sotre the restaurant name
//						// Store next value into postal code
//			iss >> restaurantName >> postalCode;
//			restaurantDatabase[numberOfRestaurants] = Restaurant(restaurantName, postalCode);
//			numberOfRestaurants++;
//		}
//		else if (firstWord == "FoodItem")
//		{
//			// create temp
//			string name, description, category;
//			double price;
//			iss >> name >> description >> category >> price;
//			FoodItem tempFoodItem(name, description, category, price);
//			// -1 index start at0
//			restaurantDatabase[numberOfRestaurants - 1].restaurantMenuPointer()->insertNode(tempFoodItem);
//		}
//
//	}
//	file.close();
//}
//
//// Write Food items
//void writeFoodItems(ofstream& file, AVLNode* root)
//{
//	if (root == nullptr)
//		return;
//
//	// Write left subtree
//	writeFoodItems(file, root->left);
//
//	// Write current food item
//	file << "FoodItem " << root->foodItem.getName() << " " << root->foodItem.getFoodDescription()
//		<< " " << root->foodItem.getCategory() << " " << root->foodItem.getPrice() << "\n";
//
//	// Write right subtree
//	writeFoodItems(file, root->right);
//}
//
//// Write Restaurant files
//void writeRestaurantFile(Restaurant restaurantDatabase[], int numberOfRestaurants)
//{
//	ofstream file("restaurant.txt");
//
//	for (int i = 0; i < numberOfRestaurants; i++)
//	{
//		// Write restaurant details
//		file << "Restaurant " << restaurantDatabase[i].getRestaurantName() << " " << restaurantDatabase[i].getPostalCode() << "\n";
//
//		// Write food items by traversing the AVL tree
//		writeFoodItems(file, restaurantDatabase[i].restaurantMenuPointer()->getRoot());
//	}
//
//	file.close();
//}
//
//// print restaurants
//void printRestaurants(Restaurant restaurantDatabase[], int numberOfRestaurants) {
//	cout << "Restaurants in the database:\n";
//	for (int i = 0; i < numberOfRestaurants; i++) {
//		std::cout << i+1 << ". " << "Name: " << restaurantDatabase[i].getRestaurantName()
//			<< " - Postal Code: " << restaurantDatabase[i].getPostalCode() << "\n";
//		restaurantDatabase[i].printMenu();
//	}
//}
//
//// print restaurants titles
//void printRestaurantsTitles(Restaurant restaurantDatabase[], int numberOfRestaurants) {
//	cout << "Restaurants in the database:\n";
//	for (int i = 0; i < numberOfRestaurants; i++) {
//		std::cout << i + 1 << ". " << "Name: " << restaurantDatabase[i].getRestaurantName()
//			<< " - Postal Code: " << restaurantDatabase[i].getPostalCode() << "\n";
//	}
//}

// USERS
// Functions 1 : Login
// Pre : Should only be when logged out
// Post: Return a true or false statement 
bool login(string& userInputEmail,string& userInputPassword,
           CustomerDictionary& aCustomerDictionary)
{
	// Step 1: Hash the user input password
	string hashedPassword = hashPassword(userInputPassword);

	// Step 2: Check if emailkey is inside the dictionary
	// If it is not inside, comparedHash = "USERNOTFOUND"
	string comparedHash = aCustomerDictionary.retrievePassword(userInputEmail);
	if (comparedHash == hashedPassword)
	{
		cout << "Authentication success" << endl;
		return true;
	}
	else
	{
		cout << "Something went wrong, please try logging in again" << endl;
		cout << "-------------------------------------------------" << endl;
		return false;
	}
}

// Function 2 : Register
// Register New Customer
// Pre : Should only be when logged out
bool registerCustomerAccount(const string& userInputEmail, const string& userInputPassword,
	const string& userInputName, int userInputPostalCode, CustomerDictionary& aCustomerDictionary)
{

	// Step 1: Hash the user input password
	string hashedPassword = hashPassword(userInputPassword);

	// Step 2: Create a temporary user 
	Customer tempUser =  Customer(userInputEmail, hashedPassword, 
		userInputName, userInputPostalCode );

	// STep 3: Add the user
	bool addCustomerSuccess = aCustomerDictionary.addCustomer(userInputEmail, tempUser);

	// Step 4 : Check if adding into dictionary is successful, return false if failed.
	if (addCustomerSuccess == false)
	{
		cout << "User already exists." << endl;
		return false;
	}

	// Step 5 : Otherwise, adding is succesful return as true
	
	return true;
}

// Function 3 : display UI for register and display

// STAFF
// Functions 1 : Login
// Pre : Should only be when logged out
// Post: Return a true or false statement 
bool stafflogin(const string& staffInputEmail, const string& staffInputPassword, 
	StaffDictionary& aStaffDictionary)
{
	// Step 1: Hash the staff input password
	string hashedPassword = hashPassword(staffInputPassword);

	// Step 2: Check if emailkey is inside the dictionary
	// If it is not inside, comparedHash = "USERNOTFOUND"
	string comparedHash = aStaffDictionary.retrievePassword(staffInputEmail);
	if (comparedHash == hashedPassword)
	{
		cout << "Authentication success" << endl;
		return true;
	}
	else
	{
		cout << "Something went wrong, please try logging in again" << endl;
		cout << "-------------------------------------------------" << endl;
		return false;
	}
}

// Function 2 : Register
// Register New staff
// Pre : Should only be when logged out
bool registerStaffAccount(string& email, string& password, Restaurant* aRestaurantPointer, 
	StaffDictionary& staffDatabase)
{
	// Step 1: Hash the user input password
	string hashedPassword = hashPassword(password);

	// Step 2: Create a temporary restaurant staff object
	RestaurantStaff tempStaff = RestaurantStaff(email, hashedPassword, aRestaurantPointer);
	tempStaff.setRestaurantName(aRestaurantPointer->getRestaurantName());

	// Step 3: Add the restaurant staff to the database
	bool addStaffSuccess = staffDatabase.addStaff(email, tempStaff);

	if (!addStaffSuccess)
	{
		cout << "Restaurant staff account already exists." << endl;
		return false;
	}

	// Save the new restaurant staff details to the text file
	staffDatabase.saveToFile();

	cout << "Restaurant staff registration successful!" << endl;
	return true;
}

int main()
{
	// Initialize restaurants
	Restaurant restaurantDatabase[MAX_RESTAURANTS];

	RestaurantArray testingArray;

	testingArray.printRestaurants();

	int numberOfRestaurants = 0;
	/////readRestaurantFile(restaurantDatabase, numberOfRestaurants);
	// Initalize staff database
	StaffDictionary staffDatabase = StaffDictionary();
	staffDatabase.loadFromFile(restaurantDatabase, numberOfRestaurants);
	// Initaliaze user database
	CustomerDictionary userDatabase = CustomerDictionary();
	

	// Set-up and exit condition for UI
	Customer customer = Customer();
	RestaurantStaff* restaurantStaff = nullptr;
	bool displayLandingPage = true;
	bool customerLoggedIn = false;
	bool restaurantStaffLoggedIn = false;
	string loginChoice;
	string staffEmail;

	// User presented with two choices to log in or register
	while (displayLandingPage)
	{
		// Display message and prompt for choice
		cout << " _  _  _ _______        _______  _____  _______ _______" << endl;
		cout << " |  |  | |______ |      |       |     | |  |  | |______" << endl;
		cout << " |__|__| |______ |_____ |_____  |_____| |  |  | |______" << endl;
		cout << endl;
		cout << "What would like to do?\n";
		cout << "0. admin\n1. User Login\n2. User Register\n3. Staff Login\n4. Staff Register\n" << endl;
		cout << "Your choice? (1 - 4) : ";
		cin >> loginChoice;

		if (loginChoice == "1" || loginChoice == "2" || loginChoice == "0")
		{
			// Temp for us to check anything fast
			if (loginChoice == "0")
			{
				//////printRestaurants(restaurantDatabase, numberOfRestaurants);
			}
			// 1. Login Function
			if (loginChoice == "1")
			{
				cout << "         _____   ______ _____ __   _" << endl;
				cout << " |      |     | |  ____   |   | |  |" << endl;
				cout << " |_____ |_____| |_____| __|__ |  |_|" << endl;
				cout << endl;
				// Store guest Information
				string guestEmail; 
				string guestPassword;

				// Step 1 : Prompt for email
				guestEmail = getUserEmailInput();
				// Step 2 : Prompt for password
				cout << "Please enter your password : ";
				cin >> guestPassword;

				// Check if login is success 
				if (login(guestEmail, guestPassword, userDatabase))
				{
					// On log in success, 
					customerLoggedIn = true;
					userDatabase.retrieveUser(guestEmail, customer);
					break;
				}

			}

			// 2. Register function
			if (loginChoice == "2")
			{	                             

				cout << "  ______ _______  ______ _____ _______ _______ _______  ______" << endl;
				cout << " |_____/ |______ |  ____   |   |______    |    |______ |_____/" << endl;
				cout << " |    L_ |______ |_____| __|__ ______|    |    |______ |    L_" << endl;
				cout << endl;
				// Store guest Information
				string guestEmail;
				string guestPassword;
				string guestName;
				int guestPostalCode;

				// Step 1 : Prompt for Details
				guestEmail = getUserEmailInput();

				cout << "Please set your password : " ;
				cin >> guestPassword;

				cout << "Please set your name : " ;
				cin >> guestName;

				guestPostalCode = getValidatedInt();

				// Step 3: Prompt 
				cout << "Registering..." << endl;
				bool registrationSuccess = registerCustomerAccount(guestEmail, guestPassword, 
					guestName, guestPostalCode, userDatabase);
				
				// If error show response
				if (!registrationSuccess)
				{
					cout << "Something went wrong, please try again" << endl;
					cout << "--------------------------------------" << endl;
					continue;
					
				}

				// If success show message
				cout << "Registration successful! Please proceed to log in" << endl;
				cout << "-------------------------------------------------" << endl;

				// Save the new user details to the text file
				userDatabase.saveToFile();
			}

			// 3. 
		}

		if (loginChoice == "4" || loginChoice == "3")
		{
			if (loginChoice == "3")
			{
				// Restaurant staff login
				cout << "Restaurant Staff Login" << endl;
				string staffPassword;

				staffEmail = getUserEmailInput();

				cout << "Please enter your password: ";
				cin >> staffPassword;

				// Check staff login
				if (stafflogin(staffEmail, staffPassword, staffDatabase))
				{
					cout << "Restaurant staff login successful!" << endl;
					restaurantStaffLoggedIn = true;
					break;
				}
				else
				{
					cout << "Invalid email or password for restaurant staff." << endl;
				}
			}
			if (loginChoice == "4")
			{
				// Restaurant staff registration
				cout << "Restaurant Staff Registration" << endl;
				string staffPassword;
				Restaurant* restaurantChosen = nullptr;

				staffEmail = getUserEmailInput();

				cout << "Please enter your password: ";
				cin >> staffPassword;
				
				// Create an array of valid inputs
				// Start at index zero, but value start at 1
				string restaurantChoices[MAX_RESTAURANTS];
				for (int i = 0; i < numberOfRestaurants; i++)
				{
					restaurantChoices[i] = to_string(i + 1);
				}
				
				// Create exit condition
				bool validRestaurantChoice = false;
				string restaurantChoice;
				///////printRestaurantsTitles(restaurantDatabase, numberOfRestaurants);
				
				// Prompt user to select restaurant to order from
				while (!validRestaurantChoice)
				{

					cout << "Please enter the restaurant you are assigned to: ";
					cin >> restaurantChoice;
					bool found = false;
					// If it is not valid 

					for (int i = 0; i < numberOfRestaurants; i++)
					{
						if (restaurantChoice == restaurantChoices[i])
						{
							validRestaurantChoice = true;
							restaurantChosen = &restaurantDatabase[stoi(restaurantChoice) - 1];
							found = true;
							break;
						}
					}
					// Exit out of for loop
					if (found)
					{
						break;
					}
					else
						cout << "Please enter appropriate integer corresponding to restaurant" << endl;

				}


				if (registerStaffAccount(staffEmail, staffPassword, restaurantChosen, staffDatabase))
				{
					cout << "You are now registered as restaurant staff!" << endl;
				}
			}
		}

		
		// For any invalid menu options
		else
		{
			cout << "Invalid input. Redirecting back to menu" << endl;
			cout << "---------------------------------------" << endl;
		}
	}

	if (customerLoggedIn)
	{
		// Pre - process lists of food
		// Default is A-Z 
		// If they want to  view in reverse order, use a stack 
		const int MAX_FOOD_LIST_CAP = 10000;
		//FoodItem* ascendingNameFoodList[MAX_FOOD_LIST_CAP];
		//FoodItem* ascendingCategoryFoodList[MAX_FOOD_LIST_CAP];
		//FoodItem* ascendingPriceFoodList[MAX_FOOD_LIST_CAP];	
		// INSERT OPERATIONS


		// Present interface for the user
		cout << "====================================================" << endl;
		cout << "Welcome Back" << endl;
		cout << "What would you like to do?" << endl;
		cout << "1. Create new order\n2. Check order\n3. Cancel Order\n4. Log out" << endl;
		
		// While loop for prompt
		bool validCustomerResponse = false;
		string customerInput;

		while (!validCustomerResponse)
		{
			cout << "Your choice ? : ";
			cin >> customerInput;

			// 3 options
			if (customerInput == "1")
			{
				cout << "____ ____ ____ ____ ___ ____    _  _ ____ _ _ _    ____ ____ ___  ____ ____ " << endl;
				cout << "|    |__/ |___ |__|  |  |___    || | |___ | | |    |  | |__/ |  | |___ |__/ " << endl;
				cout << "|___ |  | |___ |  |  |  |___    | || |___ |_|_|    |__| |  | |__/ |___ |  | " << endl;
				cout << "                                                                            " << endl;  
				
				// Display UI for restaurants and their menus
				//////printRestaurants(restaurantDatabase, numberOfRestaurants);
				
				// Create the temporary order
				Order* temporaryOrder = nullptr;

				// Create an array of valid inputs
				// Start at index zero, but value start at 1
				string restaurantChoices[MAX_RESTAURANTS];
				for (int i = 0; i < numberOfRestaurants; i++)
				{
					restaurantChoices[i] = to_string(i + 1);
				}

				// Create exit condition
				bool validRestaurantChoice = false;
				string restaurantChoice; 
				Restaurant* restaurantChosen = nullptr; // Initialize the pointer to nullptr
				// This is the one that is ultimately selected

				// Prompt user to select restaurant to order from
				while (!validRestaurantChoice)
				{
					cout << "which restaurant would you like to order from? : ";
					cin >> restaurantChoice;
					bool found = false;
					// If it is not valid 

					for (int i = 0; i < numberOfRestaurants; i++)
					{
						if (restaurantChoice == restaurantChoices[i])
						{
							validRestaurantChoice = true;
							restaurantChosen = &restaurantDatabase[stoi(restaurantChoice) - 1];
							temporaryOrder = customer.createNewOrder(restaurantChosen);
							found = true;
							break;
						}
					}
					// Exit out of for loop
					if (found)
					{
						cout << "Creating an empty order form..." << endl;
						break;
					}
					else
						cout << "Please enter appropriate integer corresponding to restaurant" << endl;
					
				}
				// Broke out of while loop - Order is created
				// Show that specific restaurant menu to prompt user
				restaurantChosen->printMenu();
				cout << "What would you like to order?" << endl;
				// 
				bool isOrderConfirmed = false;

				// While not confirmed and not full, allow adding of food items
				while (!isOrderConfirmed && !temporaryOrder->isFull())
				{
					// temp
					FoodItem* foodItemPointer = nullptr;
					string foodItemName;
					// prompt user
					cout << "Type the exact name of the food you would like to order" << endl;
					cin >> foodItemName;

					// search in the menu if it exists
					foodItemPointer = restaurantChosen->restaurantMenuPointer()->searchNode(foodItemName);

					if (foodItemPointer == nullptr)
					{
						cout << "Food item does not exist, please try again";
					}
					else
					{
						cout << foodItemPointer->getName() << " has been added to your order.";
					}

					//if (temporaryOrder.)
				}
				


				// 

				// 
				
			}
			else if (customerInput == "2")
			{
				cout << "____ _  _ ____ ____ _  _    ____ ____ ___  ____ ____ " << endl;
				cout << "|    |__| |___ |    |_/     |  | |__/ |  | |___ |__/ " << endl;
				cout << "|___ |  | |___ |___ | |_    |__| |  | |__/ |___ |  | " << endl;
				cout <<                                                      "" << endl;

			}
			else if (customerInput == "3")
			{
				cout << "____ ____ _  _ ____ ____ _       ____ ____ ___  ____ ____ " << endl;
				cout << "|    |__| || | |    |___ |       |  | |__/ |  | |___ |__/ " << endl;
				cout << "|___ |  | | || |___ |___ |___    |__| |  | |__/ |___ |  | " << endl;
				cout << "                                                          " << endl;
			}
			else
			{
				cout << "Invalid input, please try select appropriate number" << endl;
				continue;
			}
		}
		// Break out of user options menu
	}
	if (restaurantStaffLoggedIn)
	{
		restaurantStaff = staffDatabase.search(staffEmail);
		
		// Present interface for the user
		cout << "====================================================" << endl;
		cout << "Welcome Back, " << restaurantStaff->getRestaurantName() << endl;
		while (true)
		{
			cout << "1. View Incoming Orders\n2. View customer information of latest order\n3. Update Order\n4. Generate Report\n5. Add food item To Menu\n6. Edit food item\n7. View Menu" << endl;
			cout << "What would you like to do? ";
			// Get input from user
			string staffInput;
			cin >> staffInput;

			// If input is 1
			if (staffInput == "1")
			{
				// Print out all the orders
				restaurantStaff->viewAllOrders();
			}
			else if (staffInput == "2")
			{
				// Print out the latest order
				
			}
			else if (staffInput == "3")
			{
				// Update order

			}
			else if (staffInput == "4")
			{
				// Generate report
			}
			else if (staffInput == "5")
			{
				// Add food item to menu
				restaurantStaff->addFoodItem(restaurantStaff);
				// Save changes to the restaurant.txt file after adding the food item
				/////writeRestaurantFile(restaurantDatabase, numberOfRestaurants);
			}
			else if (staffInput == "6")
			{
				// Edit food item
				while (true)
				{
					restaurantStaff->getRestaurantPointer()->printMenu();
					cout << "Which food item would you like to edit? (q to quit)" << endl;

					string foodItemName;
					cin >> foodItemName;
					
					if (foodItemName == "q")
						break;
					
					FoodItem* foodItemPointer = restaurantStaff->getRestaurantPointer()->restaurantMenuPointer()->searchNode(foodItemName);
					if (foodItemPointer == nullptr)
					{
						cout << "Food item does not exist, please try again" << endl;
					}
					else
					{
						restaurantStaff->updateFoodItem(foodItemPointer);
						// Save changes to the restaurant.txt file after updating the food item
						///////writeRestaurantFile(restaurantDatabase, numberOfRestaurants);
					}

				}
				
			}
			else if (staffInput == "7")
			{
				// View menu
				restaurantStaff->getRestaurantPointer()->printMenu();
			}
			else
			{
				cout << "Invalid input, please try select appropriate number" << endl;
			}
		}

	}

}
// DSA Diamond Hands Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once

#include <iostream>
#include "User.h"
#include "CustomerDictionary.h"
#include "Customer.h"

using namespace std;

// INPUT HELPERS
string hashPassword(string aUnhashedPassword)
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
	size_t atIndex = email.find('@');
	size_t dotIndex = email.rfind('.');

	// Check if '@' and '.' are both present and in the correct order
	// if index is -1, means not present
	if (atIndex == -1 || dotIndex == -1 || atIndex > dotIndex) {
		return false;
	}

	// Check for ".com" domain nane
	string domain = email.substr(dotIndex + 1);
	if (domain != "com") {
		return false;
	}

	// Check for alphanumeric characters before '@'
	string localPart = email.substr(0, atIndex);
	// Iterate through the characters
	for (char c : localPart) {
		if (!isalnum(c)) {
			return false;
		}
	}
	return true;
}
// Check if valid postal code
// Postal Codes in SG are all 6 digits long , any digit is OK
bool isValidPostalCode(string& input)
{
	if (input.length() != 6) {
		return false;
	}
	for (char c : input) {
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
}

// Similar function but for int values 
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
}


// USERS
// Functions 1 : Login
// Pre : Should only be when logged out
// Post: Return a true or false statement 
bool login(string userInputEmail, string userInputPassword, CustomerDictionary& aCustomerDictionary)
{
	// Step 1: Hash the user input password
	string hashedPassword = hashPassword(userInputPassword);

	// Step 2: Check if emailkey is inside the dictionary
	// If it is not inside, comparedHash = "USERNOTFOUND"
	string comparedHash = aCustomerDictionary.retrieve(userInputEmail);
	if (comparedHash == hashedPassword)
	{
		cout << "Authentication success" << endl;
		cout << "----------------------" << endl;
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
bool registerAccount(string userInputEmail, string userInputPassword, 
	string userInputName, int userInputPostalCode, CustomerDictionary& aCustomerDictionary)
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

int main()
{
	// Initaliaze user database
	CustomerDictionary userDatabase = CustomerDictionary();

	// Set-up and exit condition for UI
	bool displayLogin = true;
	string loginChoice;

	// User presented with two choices to log in or register
	while (displayLogin)
	{
		// Display message and prompt for choice
		cout << " _  _  _ _______        _______  _____  _______ _______" << endl;
		cout << " |  |  | |______ |      |       |     | |  |  | |______" << endl;
		cout << " |__|__| |______ |_____ |_____  |_____| |  |  | |______" << endl;
		cout << endl;;
		cout << "What would like to do?\n";
		cout << "0.admin\n1. Login\n2. Register\n";
		cout << "Your choice? (1 - 2) : ";
		cin >> loginChoice;

		if (loginChoice == "1" || loginChoice == "2" || loginChoice == "0")
		{
			if (loginChoice == "0")
			{
				userDatabase.printEverything();
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
					cout << "Welcome Back" << endl;
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
				bool registrationSuccess = registerAccount(guestEmail, guestPassword, 
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

			}
			// 3. 
		}
		// For any invalid menu options
		else
		{
			cout << "Invalid input. Redirecting back to menu" << endl;
			cout << "---------------------------------------" << endl;
		}
	}
   
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

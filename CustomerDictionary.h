/*
 * T03 Jonathan Ho S10246045 Ong Jun Jie S10240117
 * Done by Jonathan Ho 
 */
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>	
#include "User.h"
#include "Customer.h"

// Forward declaration
class Customer;

using namespace std;

// Hard ceiling of users
const int CUSTOMER_MAX_SIZE = 5;

// Dictionary structure containing user objects
struct CustomerNode
{
	string emailKey; // Search Key
	Customer customer; // Data item
	CustomerNode* next = nullptr; // Pointer to next item
};

class CustomerDictionary
{
private:
	// Attributes
	CustomerNode* customers[CUSTOMER_MAX_SIZE];
	int size;

public:
	// Constructor for the Dictionary
	CustomerDictionary();
	~CustomerDictionary();

	// Hash the key that will be used to search
	// Pre : ~
	// Post: Returns INT value based on hash algorithm hashedKey
	int getHashedKey(string& aEmailKey);

	// Prompts user and Simple validator
	// Pre : ~
	// Post: get a valid email string
	string getValidEmail();

	// Prompts user and Check if valid postal code 
	// Postal Codes in SG are all 6 digits long , any digit is OK
	// Post: get a valid postal code int
	int getValidPostalCode();

	// Add new item with the specified key to the Dictionary
	// Pre : EmailKey must be in email format
	// Post: New item added to dictionary
	bool addCustomer(string aEmailKey, Customer& aCustomer);

	// Retrieve the hashedpw that matches the hashedKey
	// Pre : The hashedKey must match at least one of the results 
	// Post: Returns the hashedpw
	string retrievePassword(string& aEmailKey);

	// Retrieve the user that matches the email key
	// Pre : ~
	// Post: Returns the user
	bool retrieveUser(string& aEmailKey, Customer& aCustomer);

	// Check if Dictionary is empty
	// Pre  : ~
	// Post : Returns true if there nothing in the dictionary
	bool isEmpty();

	// loads data from file
	// Pre : ~
	// Post: ~
	void loadFromFile();

	// saves data to file
		// Pre : ~
	// Post: ~
	void saveToFile();

	// INPUT HELPERS
	// Hash the password for security reasons
	string hashPassword(string& aUnhashedPassword);

	// Login Function for customers
	// Pre : Should only be when logged out
	// Post: Return a true if successful
	bool customerLogin(Customer*& aCustomer);

	// Register New Customer
	// Pre : Should only be when logged out
	// Post: Return true if succesful
	bool registerCustomerAccount();

	// searches for a user in the dictionary, returns a pointer to the user if found
	// Pre  : aEmailKey must be in email format
	// Post : returns user if found else nullptr
	Customer* search(string aEmail);
};

	
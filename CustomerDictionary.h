#pragma once
#include <iostream>
#include <string>
#include "User.h"
#include <fstream>
#include "Customer.h"

// Forward declaration
class Customer;

using namespace std;

// Hard ceiling of users
const int CUSTOMER_MAX_SIZE = 5;

// Dictionary structure containing user objects
struct CustomerNode
{
	string emailKey;			// Search Key
	Customer customer;					// Data item
	CustomerNode* next = nullptr;	// Pointer to next item
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

	// Add new item with the specified key to the Dictionary
	// Pre : EmailKey must be in email format
	// Post: New item added to dictionary
	bool addCustomer(string aEmailKey, Customer& aCustomer);

	// Retrieve the hashedpw that matches the hashedKey
	// Pre : The hashedKey must match at least one of the results 
	// Post: Returns the hashedpw
	string retrievePassword(string& aEmailKey);

	// Retrieve the user that matches the email key
	// Pre : 
	// Post: Returns the user
	bool retrieveUser(string& aEmailKey, Customer& aCustomer);

	// Check if Dictionary is empty
	// Pre  : ~
	// Post : Returns true if there nothing in the dictionary
	bool isEmpty();

	// loads data from file
	void loadFromFile();
	// saves data to file
	void saveToFile();

	// INPUT HELPERS
	string hashPassword(string& aUnhashedPassword);

	// Pre : Should only be when logged out
	// Post: Return a true or false statement 
	bool customerLogin(Customer* aCustomer);

	// Register New Customer
	// Pre : Should only be when logged out
	bool registerCustomerAccount();

	// Simple validator
	string getValidEmail();

	// Check if valid postal code
	// Postal Codes in SG are all 6 digits long , any digit is OK
	int getValidPostalCode();
};

	
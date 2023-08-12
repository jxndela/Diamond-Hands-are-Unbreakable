#pragma once
#include <iostream>
#include <string>
#include "User.h"
#include "Customer.h"


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

	// TODO: Parameterized constructor for dictionary (used to initialize dictionary with existing data from .txt file)
	// Pre : Valid URL file path
	// Post: Constructs Dictionary with values stored
	// UserDictionary(string txtfilepath)

	// Hash the key that will be used to search
	// Pre : ~
	// Post: Returns INT value based on hash algorithm hashedKey
	int getHashedKey(string aEmailKey);

	// Add new item with the specified key to the Dictionary
	// Pre : EmailKey must be in email format
	// Post: New item added to dictionary
	bool addCustomer(string aEmailKey, Customer& aCustomer);

	// Retrieve the hashedpw that matches the hashedKey
	// Pre : The hashedKey must match at least one of the results 
	// Post: Returns the hashedpw
	string retrievePassword(string aEmailKey);

	// Check if Dictionary is empty
	// Pre  : ~
	// Post : Returns true if there nothing in the dictionary
	bool isEmpty();

	// Temporary
	void printEverything()
	{
		CustomerNode* current;
		for (int i = 0; i < CUSTOMER_MAX_SIZE; i++)
		{
			current = customers[i];
			while (current != nullptr)
			{
				string var1 = current->customer.getEmail();
				string var2 = current->customer.getPasswordHash();
				string var3 = current->customer.getCustomerName();
				int var4 = current->customer.getCustomerPostalCode();
				cout << endl;
				cout << "email: " << var1 << endl;
				cout << "pw: " << var2 << endl;
				cout << "name: " << var3 << endl;
				cout << "postal : " << var4 << endl;
				current = current->next;
			}
		}
	}
};


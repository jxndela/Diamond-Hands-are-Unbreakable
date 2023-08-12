#include "CustomerDictionary.h"

// Constructor for the Dictionary
CustomerDictionary::CustomerDictionary()
{
	// Initialize the values in each index of the users array and assign nullptr
	for (int i = 0; i < CUSTOMER_MAX_SIZE; i++)
	{
		customers[i] = nullptr;
	}
	// Set default size to 0
	size = 0;
}

CustomerDictionary::~CustomerDictionary()
{
	// Iterate through each bucket
	for (int i = 0; i < CUSTOMER_MAX_SIZE; ++i) {
		// Delete linked list nodes in the current bucket
		CustomerNode* current = customers[i];
		while (current != nullptr) {
			CustomerNode* temp = current;
			current = current->next;
			delete temp;
		}
	}
}

// Hash the key that will be used to search
// Pre : ~
// Post: Returns INT value based on hash algorithm hashedKey
int CustomerDictionary::getHashedKey(string aEmailKey)
{
	// TEMPORARY HASH FUNCTION
	int sum = 0;
	for (int i = 0; i < aEmailKey.length(); i++)
	{
		sum += aEmailKey[i];
	}
	return sum % CUSTOMER_MAX_SIZE;
}

// Add new item with the specified key to the Dictionary
// Pre : EmailKey must be input validated beforehand. This emailKey comes from user input
//       User Object is created 
// Post: New item added to dictionary, returns true. Otherwise return false
bool CustomerDictionary::addCustomer(string aEmailKey, Customer& aCustomer)
{
	// Hash the email key to obtain index of the user
	int index = CustomerDictionary::getHashedKey(aEmailKey);

	// If space contains a nullptr, start new linked list 
	if (customers[index] == nullptr)
	{
		// Create a new node, entering the aEmailKey as well as the User Object
		customers[index] = new CustomerNode;
		customers[index]->emailKey = aEmailKey;
		customers[index]->customer = aCustomer;
		customers[index]->next = nullptr;
	}
	// Otherwise, a collision has occured i.e. Index is the same
	else
	{
		CustomerNode* current = customers[index];

		// Duplicate key on first in chain (User is already registered)
		if (current->emailKey == aEmailKey)
		{
			return false;
		}
			

		// Iterate through the chain as long next is not nullptr
		while (current->next != nullptr)
		{
			current = current->next;
			// Check for duplicate user object in the rest of chain
			// User objects cannot be associated with 2 email keys simultaneously 
			if (current->customer.getEmail() == aCustomer.getEmail())
			{
				// If matched, it means that user exists at some point of the chain
				return false;
			}

		}

		// Exited while loop, no users matched
		CustomerNode* newUserNode = new CustomerNode;
		newUserNode->emailKey = aEmailKey;
		newUserNode->customer = aCustomer;
		newUserNode->next = nullptr;
		current->next = newUserNode;
	}

	// Increment size
	size++;

	// Return true as user has been added.
	return true;
}

string CustomerDictionary::retrievePassword(string aEmailKey)
{
	// Hash the email key to obtain index of the user
	int index = getHashedKey(aEmailKey);

	// Search for key in determiend index

	CustomerNode* current = customers[index];
	while (current != nullptr)
	{
		// If key is found return the user object that is in current node
		if (current->emailKey == aEmailKey)
		{
			return current->customer.getPasswordHash();
		}
		// Else, continue to the next node
		current = current->next;
	}
	// Exited while loop, key is not found
	return "USERNOTFOUND";
}

bool CustomerDictionary::retrieveUser(string aEmailKey, Customer& aCustomer)
{
	// hash email
	int index = getHashedKey(aEmailKey);

	// Search for key
	CustomerNode* current = customers[index];
	while (current != nullptr)
	{
		// return user if key found and true
		if (current->emailKey == aEmailKey)
		{
			aCustomer = current->customer;
			return true;
		}
		// else move on
		current = current->next;
	}
	return false;
}



bool CustomerDictionary::isEmpty()
{
	return size == 0;
}

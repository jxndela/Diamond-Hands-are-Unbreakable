#pragma once
#include <iostream>
#include <string>
#include "User.h"
#include "RestaurantStaff.h"

// Forward declaration
class RestaurantStaff;

using namespace std;

// Hard ceiling of users
const int CUSTOMER_MAX_SIZE = 5;

struct RestaurantStaffNode
{
	string emailKey;			// Search Key
	RestaurantStaff staff;					// Data item
	RestaurantStaffNode* next = nullptr;	// Pointer to next item
};


class StaffDictionary
{
private:
	// Attributes
	RestaurantStaffNode* staffs[CUSTOMER_MAX_SIZE];
	int size;
	

public:
	// Constructor for the Dictionary
	StaffDictionary();
	~StaffDictionary();

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
	bool addStaff(string aEmailKey, RestaurantStaff& aStaff);

	// Retrieve the hashedpw that matches the hashedKey
	// Pre : The hashedKey must match at least one of the results 
	// Post: Returns the hashedpw
	string retrievePassword(string aEmailKey);

	// Retrieve the user that matches the email key
	// Pre : 
	// Post: Returns the user
	bool retrieveUser(string aEmailKey, RestaurantStaff& aStaff);

	// Check if Dictionary is empty
	// Pre  : ~
	// Post : Returns true if there nothing in the dictionary
	bool isEmpty();


	// loads data from file
	void loadFromFile();
	// saves data to file
	void saveToFile();
};





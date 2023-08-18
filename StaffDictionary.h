#pragma once
#include <iostream>
#include <string>

#include "User.h"
#include "RestaurantStaff.h"

// Forward declaration
class RestaurantStaff;

using namespace std;

// Hard ceiling of users
const int STAFF_MAX_SIZE = 5;

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
	RestaurantStaffNode* staffs[STAFF_MAX_SIZE];
	int size;


public:
	// Constructor for the Dictionary
	StaffDictionary();
	~StaffDictionary();

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
	void loadFromFile(Restaurant restaurantDatabase[], int numberOfRestaurants);
	/*void loadFromFile();*/
	// saves data to file
	void saveToFile();

	// searches for a user in the dictionary, returns a pointer to the user if found
	// Pre  : aEmailKey must be in email format
	// Post : returns true if user is found
	RestaurantStaff* search(string email);

	// INPUT HELPERS
	string hashPassword(string& aUnhashedPassword);

	// Simple validator
	string getValidEmail();

	// Check if valid postal code
	// Postal Codes in SG are all 6 digits long , any digit is OK
	int getValidPostalCode();

	// STAFF
	// Functions 1 : Login
	// Pre : Should only be when logged out
	// Post: Return a true or false statement 
	bool stafflogin(RestaurantStaff* aStaff);

	// Function 2 : Register
	// Register New staff
	// Pre : Should only be when logged out
	bool registerStaffAccount(RestaurantArray aRestaurantDatabase);

	// D
	// Function 3 : Edit Food Items
	void editFoodItems(RestaurantStaff* restaurantStaff);
};

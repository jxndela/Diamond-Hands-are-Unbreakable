#include "StaffDictionary.h"
#include <fstream>

// Constructor for the Dictionary
StaffDictionary::StaffDictionary()
{
	// Initialize the values in each index of the users array and assign nullptr
	for (int i = 0; i < STAFF_MAX_SIZE; i++)
	{
		staffs[i] = nullptr;
	}
	// Set default size to 0
	size = 0;

}

StaffDictionary::~StaffDictionary()
{
	// Save user details to file before exiting
	saveToFile();

	// Iterate through each bucket
	for (int i = 0; i < STAFF_MAX_SIZE; ++i) {
		// Delete linked list nodes in the current bucket
		RestaurantStaffNode* current = staffs[i];
		while (current != nullptr) {
			RestaurantStaffNode* temp = current;
			current = current->next;
			delete temp;
		}
	}
}

// Hash the key that will be used to search
// Pre : ~
// Post: Returns INT value based on hash algorithm hashedKey
int StaffDictionary::getHashedKey(string aEmailKey)
{
	// TEMPORARY HASH FUNCTION
	int sum = 0;
	for (int i = 0; i < aEmailKey.length(); i++)
	{
		sum += aEmailKey[i];
	}
	return sum % STAFF_MAX_SIZE;
}

// Add new item with the specified key to the Dictionary
// Pre : EmailKey must be input validated beforehand. This emailKey comes from user input
//       User Object is created 
// Post: New item added to dictionary, returns true. Otherwise return false
bool StaffDictionary::addStaff(string aEmailKey, RestaurantStaff& aStaff)
{
	// Hash the email key to obtain index of the user
	int index = StaffDictionary::getHashedKey(aEmailKey);

	// If space contains a nullptr, start new linked list 
	if (staffs[index] == nullptr)
	{
		// Create a new node, entering the aEmailKey as well as the User Object
		staffs[index] = new RestaurantStaffNode;
		staffs[index]->emailKey = aEmailKey;
		staffs[index]->staff = aStaff;
		staffs[index]->next = nullptr;
	}
	// Otherwise, a collision has occured i.e. Index is the same
	else
	{
		RestaurantStaffNode* current = staffs[index];

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
			if (current->staff.getEmail() == aStaff.getEmail())
			{
				// If matched, it means that user exists at some point of the chain
				return false;
			}

		}

		// Exited while loop, no users matched
		RestaurantStaffNode* newUserNode = new RestaurantStaffNode;
		newUserNode->emailKey = aEmailKey;
		newUserNode->staff = aStaff;
		newUserNode->next = nullptr;
		current->next = newUserNode;
	}

	// Increment size
	size++;

	// Return true as user has been added.
	return true;
}

string StaffDictionary::retrievePassword(string aEmailKey)
{
	// Hash the email key to obtain index of the user
	int index = getHashedKey(aEmailKey);

	// Search for key in determiend index

	RestaurantStaffNode* current = staffs[index];
	while (current != nullptr)
	{
		// If key is found return the user object that is in current node
		if (current->emailKey == aEmailKey)
		{
			return current->staff.getPasswordHash();
		}
		// Else, continue to the next node
		current = current->next;
	}
	// Exited while loop, key is not found
	return "USERNOTFOUND";
}

bool StaffDictionary::retrieveUser(string aEmailKey, RestaurantStaff& aStaff)
{
	// hash email
	int index = getHashedKey(aEmailKey);

	// Search for key
	RestaurantStaffNode* current = staffs[index];
	while (current != nullptr)
	{
		// return user if key found and true
		if (current->emailKey == aEmailKey)
		{
			aStaff = current->staff;
			return true;
		}
		// else move on
		current = current->next;
	}
	return false;
}



bool StaffDictionary::isEmpty()
{
	return size == 0;
}


//void StaffDictionary::loadFromFile()
//{
//	ifstream inFile("staff_details.txt");
//	if (!inFile.is_open())
//	{
//
//		// Create the file if it doesn't exist
//		ofstream newFile("staff_details.txt");
//		newFile.close();
//		cout << "file has been created" << endl;
//
//		// Try opening the newly created file
//		inFile.open("staff_details.txt");
//		if (!inFile.is_open())
//		{
//			return; // Still unable to open the file
//		}
//	}
//
//	string emailKey, passwordHash;
//	while (inFile >> emailKey >> passwordHash) {
//		RestaurantStaffNode* newNode = new RestaurantStaffNode;
//		newNode->emailKey = emailKey;
//		newNode->staff.setPasswordHash(passwordHash);
//		newNode->next = nullptr;
//
//		int index = getHashedKey(emailKey);
//
//		if (staffs[index] == nullptr) {
//			staffs[index] = newNode;
//		}
//		else {
//			RestaurantStaffNode* current = staffs[index];
//			while (current->next != nullptr) {
//				current = current->next;
//			}
//			current->next = newNode;
//		}
//	}
//	inFile.close();
//}

void StaffDictionary::loadFromFile(Restaurant restaurantDatabase[], int numberOfRestaurants)
{
	ifstream inFile("staff_details.txt");
	if (!inFile.is_open())
	{
		// Create the file if it doesn't exist
		ofstream newFile("staff_details.txt");
		newFile.close();
		cout << "File has been created" << endl;

		// Try opening the newly created file
		inFile.open("staff_details.txt");
		if (!inFile.is_open())
		{
			return; // Still unable to open the file
		}
	}

	string emailKey, passwordHash, restaurantName;
	while (inFile >> emailKey >> passwordHash >> restaurantName) {
		RestaurantStaffNode* newNode = new RestaurantStaffNode;
		newNode->emailKey = emailKey;
		newNode->staff.setPasswordHash(passwordHash);

		// Find the corresponding restaurant in the restaurantDatabase
		Restaurant* associatedRestaurant = nullptr;
		for (int i = 0; i < numberOfRestaurants; ++i) {
			if (restaurantDatabase[i].getRestaurantName() == restaurantName) {
				associatedRestaurant = &restaurantDatabase[i];
				break;
			}
		}

		if (associatedRestaurant) {
			newNode->staff.setRestaurantName(restaurantName); // Set the restaurant name
			newNode->staff.setRestaurantPointer(associatedRestaurant); // Set the restaurant pointer
		}
		else {
			cout << "Associated restaurant not found for staff with email: " << emailKey << endl;
			delete newNode;
			continue;
		}

		newNode->next = nullptr;

		int index = getHashedKey(emailKey);

		if (staffs[index] == nullptr) {
			staffs[index] = newNode;
		}
		else {
			RestaurantStaffNode* current = staffs[index];
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = newNode;
		}
	}
	inFile.close();
}



void StaffDictionary::saveToFile()
{
	ofstream outFile("staff_details.txt");

	for (int i = 0; i < STAFF_MAX_SIZE; ++i) {
		RestaurantStaffNode* current = staffs[i];
		while (current != nullptr) {
			outFile << current->emailKey << " " << current->staff.getPasswordHash()
				<< " " << current->staff.getRestaurantName() << endl;
			current = current->next;
		}
	}

	outFile.close();
}

RestaurantStaff* StaffDictionary::search(string email)
{
	int index = getHashedKey(email);

	RestaurantStaffNode* current = staffs[index];
	while (current != nullptr) {
		if (current->emailKey == email) {
			return &current->staff;
		}
		current = current->next;
	}
	return nullptr;
}

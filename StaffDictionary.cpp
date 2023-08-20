#include "StaffDictionary.h"
#include "Restaurant.h"

#include <fstream>

using namespace std;

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

// Destructor
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
	int index = getHashedKey(aEmailKey);

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
			return false;
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

// Load from file
void StaffDictionary::loadFromFile(RestaurantArray* restaurantDatabase)
{
	ifstream inFile("staff_details.txt");
	if (!inFile.is_open())
	{
		// Create the file if it doesn't exist
		ofstream newFile("staff_details.txt");
		newFile.close();

		// Try opening the newly created file
		inFile.open("staff_details.txt");
		if (!inFile.is_open())
		{
			return; // Still unable to open the file
		}
	}

	string emailKey, passwordHash, restaurantName;
	Restaurant* restaurantPtr = nullptr;
	string aString;
	string line;

	while (getline(inFile, line))
	{
		stringstream ss(line);
		getline(ss, emailKey, ',');
		getline(ss, passwordHash, ',');
		getline(ss, restaurantName);
		// Find the the restaurant object
		for (int i = 0; i < restaurantDatabase->getNumberOfRestaurants(); i++)
		{
			if (restaurantDatabase->getRestaurant(i)->getRestaurantName() == restaurantName)
			{
				restaurantPtr = restaurantDatabase->getRestaurant(i);
				break;
			}
		}
		RestaurantStaff staff(emailKey, passwordHash, restaurantPtr);
		staff.setRestaurantName(restaurantName);
		addStaff(emailKey, staff);
	}
	//while (getline(inFile, emailKey, ','))
	//{
	//	getline(inFile, passwordHash, ',');
	//	getline(inFile, restaurantName);

	//	// Find the restaurant object in the database

	//	for (int i = 0; i < restaurantDatabase->getNumberOfRestaurants(); ++i) {
	//		if (restaurantDatabase->getRestaurant(i)->getRestaurantName() == restaurantName) {
	//			restaurantPtr = restaurantDatabase->getRestaurant(i);
	//			break;
	//		}
	//	}

	//	RestaurantStaff staff(emailKey, passwordHash, restaurantPtr);
	//	addStaff(emailKey, staff);
	//}
}

// Save details to the file
void StaffDictionary::saveToFile()
{
	ofstream outFile("staff_details.txt");

	for (int i = 0; i < STAFF_MAX_SIZE; ++i) {
		RestaurantStaffNode* current = staffs[i];
		while (current != nullptr) {
			outFile << current->emailKey << ","
				<< current->staff.getPasswordHash() << ","
				<< current->staff.getRestaurantName() << endl;
			current = current->next;
		}
	}

	outFile.close();
}


// searches for a user in the dictionary, returns a pointer to the user if found
// Pre  : aEmailKey must be in email format
// Post : returns true if user is found
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

string StaffDictionary::hashPassword(string& aUnhashedPassword)
{
	// TEMPORARY HASH FUNCTION
	int sum = 0;
	for (int i = 0; i < aUnhashedPassword.length(); i++)
	{
		sum += aUnhashedPassword[i];
	}
	string hashedPassword = to_string((sum % STAFF_MAX_SIZE));
	return hashedPassword;
}


string StaffDictionary::getValidEmail()
{
	bool validEmail = false;
	string staffInputEmail;
	while (!validEmail)
	{
		cout << "Please enter your email : ";
		cin >> staffInputEmail;
		// Reject empty input
		if (staffInputEmail.length() == 0)
		{
			cout << "Input cannot be empty. Please try again." << endl;
			continue;
		}
		// Check for email format
		size_t atSymbolIndex = staffInputEmail.find('@');
		size_t dotSymbolIndex = staffInputEmail.rfind('.');
		if (atSymbolIndex == -1 || dotSymbolIndex == -1 || atSymbolIndex > dotSymbolIndex)
		{
			cout << "Improper email format. Should look like example@gmail.com" << endl;
			continue;
		}
		validEmail = true;
	}
	return staffInputEmail;
}

int StaffDictionary::getValidPostalCode()
{
	bool validPostal = false;
	string staffInputPostalCode;
	while (!validPostal)
	{
		bool isAllDigits = true;
		cout << "Please enter postal code of the restaurant : ";
		cin >> staffInputPostalCode;
		// Check length
		if (staffInputPostalCode.length() != 6) {
			cout << "Please enter valid 6 digit postal code." << endl;
			continue;
		}
		for (char aChar : staffInputPostalCode) {
			if (!isdigit(aChar))
			{
				cout << "Please enter valid 6 digit postal code." << endl;
				isAllDigits = false;
			}
		}
		if (isAllDigits) break;
		validPostal = true;
	}
	// string to int and return
	return stoi(staffInputPostalCode);
}

// Pre : Should only be when logged out
// Post: Return a true or false statement 
bool StaffDictionary::stafflogin(RestaurantStaff*& aStaff)
{
	bool isExistingStaff = false;
	string staffInputEmail = getValidEmail();
	string staffInputPassword;
	cout << "Please enter a password : ";
	cin >> staffInputPassword;
	// Step 1: Hash the user input password
	string hashedPassword = hashPassword(staffInputPassword);
	// Step 2: Check if emailkey is inside the dictionary
	if (search(staffInputEmail) != nullptr)
	{
		isExistingStaff = true;
	}
	// Step 3 check password
	string comparedHash = retrievePassword(staffInputEmail);
	if (comparedHash == hashedPassword && isExistingStaff)
	{
		cout << "Authentication success" << endl;
		aStaff = search(staffInputEmail);
		return true;
	}
	cout << "Something went wrong, please try logging in again" << endl;
	cout << "-------------------------------------------------" << endl;
	return false;
}

// Register New Staff
// Pre : Should only be when logged out
bool StaffDictionary::registerStaffAccount(RestaurantArray aRestaurantDatabase)
{											
	// Get necessary inputs
	string staffInputEmail = getValidEmail();
	string staffInputPassword;
	cout << "Please enter a password : ";
	cin >> staffInputPassword;
	// Get restaurant pointer
	bool validRestaurantChoice = false;
	int staffInputRestaurant;
	Restaurant* restaurantPointer = nullptr;
	cout << "Please select restaurant that you belong to." << endl;

	aRestaurantDatabase.printRestaurants();

	while (!validRestaurantChoice)
	{
		cout << "Your choice? :	";
		cin >> staffInputRestaurant;
		if (-1 < staffInputRestaurant && staffInputRestaurant <= aRestaurantDatabase.getNumberOfRestaurants())
		{
			restaurantPointer = aRestaurantDatabase.getRestaurant(staffInputRestaurant-1);
			validRestaurantChoice = true;
			break;
		}
		cout << "Invalid input, please select a number corresponding to restaurant you belong to" << endl;
	}

	// Step 1: Hash the user input password
	string hashedPassword = hashPassword(staffInputPassword);
	// Step 2: Create a temporary user 
	RestaurantStaff tempStaff = RestaurantStaff(staffInputEmail, hashedPassword, restaurantPointer);
	tempStaff.setRestaurantName(restaurantPointer->getRestaurantName());
	// STep 3: Add the user
	bool addStaffSuccess = addStaff(staffInputEmail, tempStaff);
	// Step 4 : Check if adding into dictionary is successful, return false if failed.
	if (addStaffSuccess == false)
	{
		cout << "Staff already exists." << endl;
		cout << "---------------------" << endl;
		return false;
	}
	// Step 5 : Otherwise, adding is succesful return as true
	cout << "Registration success. Please proceed to login" << endl;
	saveToFile();
	return true;
}

//void StaffDictionary::editFoodItems(RestaurantStaff* restaurantStaff)
//{
//	while (true) {
//		restaurantStaff->getRestaurantPointer()->printMenu();
//		cout << "Which food item would you like to edit? (q to quit)" << endl;
//
//		string foodItemName;
//		cin >> foodItemName;
//
//		if (foodItemName == "q") {
//			break;
//		}
//
//		FoodItem* foodItemPointer = restaurantStaff->getRestaurantPointer()->getRestaurantMenuPointer()->searchNode(foodItemName);
//		if (foodItemPointer == nullptr) {
//			cout << "Food item does not exist, please try again" << endl;
//		}
//		else {
//			restaurantStaff->updateFoodItem(foodItemPointer);
//		}
//	}
//}


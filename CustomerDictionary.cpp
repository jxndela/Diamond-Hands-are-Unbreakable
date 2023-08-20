/*
 * T03 Jonathan Ho S10246045 Ong Jun Jie S10240117
 * Done by Jonathan Ho
 */
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
	// Load user details from file
	loadFromFile();
}

// destructor
CustomerDictionary::~CustomerDictionary()
{
	// Save user details to file before exiting
	saveToFile();
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
int CustomerDictionary::getHashedKey(string& aEmailKey)
{
	int sum = 0;
	for (int i = 0; i < aEmailKey.length(); i++)
	{
		sum += aEmailKey[i];
	}
	return sum % CUSTOMER_MAX_SIZE;
}

// Simple validator
string CustomerDictionary::getValidEmail()
{
	bool validEmail = false;
	string userInputEmail;
	while (!validEmail)
	{
		cout << "Please enter your email : ";
		cin >> userInputEmail;
		// Reject empty input
		if (userInputEmail.length() == 0)
		{
			cout << "Input cannot be empty. Please try again." << endl;
			continue;
		}
		// Check for email format
		size_t atSymbolIndex = userInputEmail.find('@');
		size_t dotSymbolIndex = userInputEmail.rfind('.');
		if (atSymbolIndex == -1 || dotSymbolIndex == -1 || atSymbolIndex > dotSymbolIndex)
		{
			cout << "Improper email format. Should look like example@gmail.com" << endl;
			continue;
		}
		validEmail = true;
	}
	return userInputEmail;
}

// Check if valid postal code
// Postal Codes in SG are all 6 digits long , any digit is OK
int CustomerDictionary::getValidPostalCode()
{
	bool validPostal = false;
	string userInputPostalCode;
	while (!validPostal)
	{
		bool isAllDigits = true;
		cout << "Please enter your postal code : ";
		cin >> userInputPostalCode;
		// Check length
		if (userInputPostalCode.length() != 6) {
			cout << "Please enter valid 6 digit postal code." << endl;
			continue;
		}
		// Check that all the characters are digits
		for (char aChar : userInputPostalCode) {
			if (!isdigit(aChar))
			{
				cout << "Please enter valid 6 digit postal code." << endl;
				isAllDigits = false;
			}
		}
		// If valid, break from while loop
		if (isAllDigits) break;
		validPostal = true;
	}
	// string to int and return
	return stoi(userInputPostalCode);
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
		// Create a current node pointer
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

string CustomerDictionary::retrievePassword(string& aEmailKey)
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

// Retrieve the user that matches the email key
// Pre :
// Post: Returns the user
bool CustomerDictionary::retrieveUser(string& aEmailKey, Customer& aCustomer)
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

// Check if Dictionary is empty
// Pre  : ~
// Post : Returns true if there nothing in the dictionary
bool CustomerDictionary::isEmpty()
{
	return size == 0;
}

void CustomerDictionary::loadFromFile()
{
	ifstream inFile("user_details.txt");
	if (!inFile.is_open())
	{
		// Create the file if it doesn't exist
		ofstream newFile("user_details.txt");
		newFile.close();

		// Try opening the newly created file
		inFile.open("user_details.txt");
		if (!inFile.is_open())
		{
			return; // Still unable to open the file
		}
	}

	// Create temp variabels
	string emailKey, passwordHash, name, postalCodeString;
	int postalCode;
	string aString;
	string line;

	// Store all the values inside the variables
	while (getline(inFile, line))
	{
		stringstream ss(line);
		getline(ss, emailKey, ',');
		getline(ss, passwordHash, ',');
		getline(ss, name, ',');
		getline(ss, postalCodeString);
		postalCode = stoi(postalCodeString);

		Customer newCustomer(emailKey, passwordHash, name, postalCode);
		addCustomer(emailKey, newCustomer);
		size++;
	}
	// close the file
	inFile.close();
}

// saves data to file
void CustomerDictionary::saveToFile()
{
	ofstream outFile("user_details.txt");

	for (int i = 0; i < CUSTOMER_MAX_SIZE; i++) {
		CustomerNode* current = customers[i];
		while (current != nullptr) {
			outFile << current->emailKey << ","
				<< current->customer.getPasswordHash() << ","
				<< current->customer.getCustomerName() << ","
				<< current->customer.getCustomerPostalCode() << endl;
			current = current->next;
		}
	}

	outFile.close();
}

// Hash password for security
string CustomerDictionary::hashPassword(string& aUnhashedPassword)
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

// Pre : Should only be when logged out
// Post: Return a true or false statement
bool CustomerDictionary::customerLogin(Customer*& aCustomer)
{
	bool isExistingCustomer = false;
	string userInputEmail = getValidEmail();
	string userInputPassword;
	cout << "Please enter a password : ";
	cin >> userInputPassword;
	// Step 1: Hash the user input password
	string hashedPassword = hashPassword(userInputPassword);
	// Step 2: Check if emailkey is inside the dictionary
	if (search(userInputEmail) == nullptr)
	{
		cout << "Something went wrong, please try logging in again" << endl;
		cout << "-------------------------------------------------" << endl;
		return false;
	}
	isExistingCustomer = true;
	// Step 3 check password
	string comparedHash = retrievePassword(userInputEmail);
	if (hashedPassword == comparedHash && isExistingCustomer)
	{
		cout << "Authentication success" << endl;
		aCustomer = search(userInputEmail);
		return true;
	}
	cout << "Something went wrong, please try logging in again" << endl;
	cout << "-------------------------------------------------" << endl;
	return false;
}

// Register New Customer
// Pre : Should only be when logged out
bool CustomerDictionary::registerCustomerAccount()
{
	string userInputEmail = getValidEmail();
	string userInputPassword;
	cout << "Please enter a password : ";
	cin.ignore();
	getline(cin, userInputPassword);
	string userInputName;
	cout << "Please enter your Name : ";
	cin.ignore();
	getline(cin, userInputName);
	int userInputPostalCode = getValidPostalCode();

	// Step 1: Hash the user input password
	string hashedPassword = hashPassword(userInputPassword);
	// Step 2: Create a temporary user
	Customer tempUser = Customer(userInputEmail, hashedPassword,
		userInputName, userInputPostalCode);
	// STep 3: Add the user
	bool addCustomerSuccess = addCustomer(userInputEmail, tempUser);
	// Step 4 : Check if adding into dictionary is successful, return false if failed.
	if (addCustomerSuccess == false)
	{
		cout << "User already exists." << endl;
		cout << "--------------------" << endl;
		return false;
	}
	// Step 5 : Otherwise, adding is succesful return as true
	cout << "Registration success. Please proceed to login" << endl;
	saveToFile();
	return true;
}
// Search for an email address and see if a user exists
// searches for a user in the dictionary, returns a pointer to the user if found
// Pre  : aEmailKey must be in email format
// Post : returns user if found else nullptr
Customer* CustomerDictionary::search(string aEmail)
{
	int index = getHashedKey(aEmail);

	CustomerNode* current = customers[index];
	while (current != nullptr) {
		if (current->customer.getEmail() == aEmail) {
			return &current->customer;
		}
		current = current->next;
	}
	return nullptr;
}
#include "Customer.h"

// Default constructor 
Customer::Customer()
{
	customerName = "guestIGuess";
	postalCode = 650367;
}

Customer::Customer(string aEmail, string aPasswordhash, string aCustomerName, int aPostalCode)
{
	email = aEmail;
	passwordHash = aPasswordhash;
	customerName = aCustomerName;
	postalCode = aPostalCode;
}

// Destructor Override ignore for now
Customer::~Customer()
{
}

// Get Customer Name
// Pre : ~
// Post: customer name 
string Customer::getCustomerName()
{
	return customerName;
}

// Get Customer Name
// Pre : ~
// Post: customer name
int Customer::getCustomerPostalCode()
{
	return postalCode;
}

string Customer::getPasswordHash()
{
	return passwordHash;
}

string Customer::getEmail()
{
	return email;
}

Order* Customer::getCurrentOrder()
{
	return currentOrder;
}


// Generate a temporary Order Variable
// Pre : No orders in progress 
// Post: Create a temporary order to store foodItems in 
// Can only order from 1 restaurant
bool Customer::createNewOrder(Order* aNewOrder, RestaurantArray* aRestaurantDatabase)
{
	// Get customer pointer, restaurant pointer
	bool isRestaurantSelected = false;
	int restaurantNumber = -1;
	Customer* customerPointer = this;
	while (!isRestaurantSelected)
	{
		// Print all available restaurants
		aRestaurantDatabase->printRestaurants();
		cout << "Please select the restaurant you wish to order from : " << endl;
		cin >> restaurantNumber;
		if (restaurantNumber < aRestaurantDatabase->getNumberOfRestaurants() &&
			0 < restaurantNumber)
		{
			// it is a valid option
			isRestaurantSelected = true;
			break;
		}
		if (restaurantNumber == 0) return false;
		else
		{
			cout << "Invalid input. Please enter a valid option." << endl;
			cout << "-------------------------------------------" << endl;
			cin.clear();                 // Clear the failed state
			cin.ignore(INT_MAX, '\n');
			continue;
		}
	}
	if (isRestaurantSelected == true)
	{
		// Set all relevant information
		Restaurant* restaurantChosen = aRestaurantDatabase->getRestaurant(restaurantNumber - 1);
		aNewOrder->setPartyInformation(customerPointer, restaurantChosen);
		aNewOrder->setCustomerName(this->getCustomerName());
		aNewOrder->setCustomerPostalCode(getCustomerPostalCode());
		aNewOrder->setRestaurantName(restaurantChosen->getRestaurantName());
	}
	return true;
}

// Confirm the order and send it to Restaurant
// Pre : Order is not empty
// Post: Send the order to the Restaurant orders queue
void Customer::confirmOrder()
{
	numberOfpreviousOrders++;
}

// Cancel an order 
// Pre : There must be an existing order that is in progress
// Post: Returns true if successful, returns false otherwise
bool Customer::cancelOrder(Order& order)
{
	return false;
}

// set password hash
void Customer::setPasswordHash(string aPasswordHash)
{
	passwordHash = aPasswordHash;
}
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

// Check customer details - this function is for RestaurantStaff to get customer info
// Pre : ~
// Post: Using pass by reference, returns the customer name and postal code
void Customer::browseFoodSelections()
{

}

// Generate a temporary Order Variable
// Pre : No orders in progress 
// Post: Create a temporary order to store foodItems in 
void Customer::createNewOrder()
{
	// 1. Show all the food options

	// 2. Show item name categpru & price and restaurant
	// 3. retrieve pointers from ARRAY after selecting item
	// 4. put inside order
	// 5. confirm order
	// 6. send order if confirmed, else return back  to while loop
}

// Confirm the order and send it to Restaurant
// Pre : Order is not empty
// Post: Send the order to the Restaurant orders queue
void Customer::confirmOrder()
{
	 
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
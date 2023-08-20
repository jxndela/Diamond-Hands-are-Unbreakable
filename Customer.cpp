#include "Customer.h"

// Default constructor 
Customer::Customer()
{
	customerName = "";
	postalCode = 000000;
}

// Parameterized constructor - set respoective fields accordingly
Customer::Customer(string aEmail, string aPasswordhash, string aCustomerName, int aPostalCode)
{
	email = aEmail;
	passwordHash = aPasswordhash;
	customerName = aCustomerName;
	postalCode = aPostalCode;
}

// Destructor
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

// Check the passwordHash of a customer object
// Pre : ~
// Post: Returns passwordHash string
string Customer::getPasswordHash()
{
	return passwordHash;
}

// Check the email of a customer object
// Pre : ~
// Post: Returns email string
string Customer::getEmail()
{
	return email;
}

// Get current order
// Pre : ~
// Post: Get pointer to the current order of the customer
Order* Customer::getCurrentOrder()
{
	return currentOrder;
}

// set password hash
// pre : ~
// post : password hash is set
void Customer::setPasswordHash(string& aPasswordHash)
{
	passwordHash = aPasswordHash;
}
// Set current order
// Pre : ~
// post: Current order replaced with a new order
void Customer::setCurrentOrder(Order* aNewOrder)
{
	currentOrder = aNewOrder;
}

// Generate a temporary Order Variable
// Pre : Order is initalized before hand
// Post: Returns true if the  
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
		cout << "Please select the restaurant you wish to order from (0 to exit) : ";
		cin >> restaurantNumber;
		cin.ignore();
		if (restaurantNumber <= aRestaurantDatabase->getNumberOfRestaurants() &&
			0 < restaurantNumber)
		{
			// it is a valid option
			isRestaurantSelected = true;
			break;
		}
		// If 0, exit straight away
		if (restaurantNumber == 0) return false;
		// Invalid 
		else
		{
			cout << "Invalid input. Please enter a valid option." << endl;
			cout << "-------------------------------------------" << endl;
			cin.clear();                 // Clear the failed state
			cin.ignore(INT_MAX, '\n');
			continue;
		}
	}
	// If restaurant is selected, then we can return true
	if (isRestaurantSelected == true)
	{
		// Set all relevant information
		Restaurant* restaurantChosen = aRestaurantDatabase->getRestaurant(restaurantNumber - 1);
		aNewOrder->setPartyInformation(customerPointer, restaurantChosen);
		aNewOrder->setCustomerName(customerName);
		aNewOrder->setCustomerPostalCode(postalCode);
		aNewOrder->setRestaurantName(restaurantChosen->getRestaurantName());
		return true;
	}
	// If restaurant fails to be selected, we return false
	return false;
}

// Add food item to an order
// Pre : Requires a order to be initalized beforehand
// Post: Order is updated with items that have been added / or not added
void Customer::addItemToOrder(Order* aNewOrder, RestaurantArray* aRestaurantDatabase)
{
	// Store selected restaurant and menu
	Restaurant selectedRestaurant = *aNewOrder->getRestaurantPointer();
	FoodItemAVL selectedMenu = *selectedRestaurant.getRestaurantMenuPointer();
	// Temporary string for customer input
	string customerFoodChoice;
	// Print menu of the restaurant
	selectedRestaurant.printMenu();
	// If already selected an item, then we show a different message
	bool isFirstItemSelected = false;
	// While loop to continuously prompt user for item to add
	while (true)
	{
		// Prompt user for input
		cout << "Please enter the exact name of dish you wish to order (Type 'exit' to finalize selection) : ";
		getline(cin, customerFoodChoice);
		// Check if input matches any of the name
		// until user types exit, we assume they want to add more, they can leave with 0 items
		if (customerFoodChoice == "exit")
			break;
		// Create temporary pointer to store
		FoodItem* tempFoodItem = selectedMenu.searchNode(customerFoodChoice);
		if (tempFoodItem == nullptr)
		{
			cout << "Please enter a valid food item name which you wish to order." << endl;
			cout << "------------------------------------------------------------" << endl;
			continue;
		}
		// Else it is successful it finding a food item, add into the order
		if (aNewOrder->addFoodItem(tempFoodItem) == false)
		{
			cout << "Addition of food item unsuccessful. Something went wrong" << endl;
			cout << "--------------------------------------------------------" << endl;
			continue;
		}
		// Print success message
		cout << "Successfully added " << tempFoodItem->getName() << " into the order." << endl;
	}
}

// Remove current order
// Pre : current order is not null
// Post: show message if nothing to remove, else show message that it has been removed
void Customer::removeCurrentOrder()
{
	if (currentOrder == nullptr)
		cout << "No order to remove. " << endl;
	else
	{
		currentOrder = nullptr;
		cout << "Current order has been set to null." << endl;
	}
}

// Confirm the order and send it to Restaurant
// Pre : Order is not empty
// Post: Send the order to the Restaurant orders queue
void Customer::confirmOrder(Order* aNewOrder)
{
	// Temp variable to store custome response
	char customerResponse;
	while (true)
	{
		// Show the order infromation, and prompt the customer
		aNewOrder->printOrderInformation();
		cout << "Would you like to confirm your order? (Order will be cancelled otherwise) Y/N : ";
		cin >> customerResponse;
		// If they do not want to confirm the order then we cancel it
		if (tolower(customerResponse) == 'n')
		{
			cout << "Order cancelled" << endl;
			delete aNewOrder;
			break;
		}
		//  If they want to confirm the order AND the order has items inside it
		if (tolower(customerResponse) == 'y' && aNewOrder->getSize() > 0)
		{
			aNewOrder->getRestaurantPointer()->getIncomingOrder()->enqueue(aNewOrder);
			cout << "Order is confirmed and has been sent to the restaurant" << endl;
			setCurrentOrder(aNewOrder);	// Change current order to this order
			break;
		}
		if (tolower(customerResponse) == 'y' && aNewOrder->getSize() == 0)
		{
			cout << "Empty order cannot be submitted, it will now be voided." << endl;
			delete aNewOrder;
			break;
		}
		cout << "Invalid response, please try again." << endl;
		cout << "-----------------------------------" << endl;
	}
}


// Cancel an order 
// Pre : There must be an existing order that is in progress
// Post: Returns true if successful, returns false otherwise
bool Customer::cancelOrder()
{
	// If no Orders we just return no orders to cancel
	if (getCurrentOrder() == nullptr)
	{
		cout << "No orders to cancel" << endl;
		return false;
	}
	cout << "Now cancelling the order" << endl;
	return true;
}


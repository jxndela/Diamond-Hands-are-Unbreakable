#include "RestaurantStaff.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
// Constructor
RestaurantStaff::RestaurantStaff()
{

}

RestaurantStaff::RestaurantStaff(string aEmail, string aPasswordhash, Restaurant* aRestaurantPointer)
{
    email = aEmail;
    passwordHash = aPasswordhash;
    restaurantPointer = aRestaurantPointer;
}


RestaurantStaff::~RestaurantStaff()
{
}

void RestaurantStaff::viewAllOrders()
{
    restaurantPointer->getIncomingOrder()->printQueue();
}

void RestaurantStaff::viewOrderAndCustomerInfo(Order aOrder)
{
    aOrder.printOrderInformation();
}

void RestaurantStaff::updateOrderStatus(Order aOrder)
{
    cout << "Order has been set to completed" << endl;
    aOrder.setOrderStatusComplete();
}

void RestaurantStaff::editOrder()
{
	//Order* orderPointer = nullptr;
	//while (true)
	//{
	//	string choice;

	//	cout << "What Order would you like to update?";
	//	restaurantPointer->getIncomingOrder()->printQueue();
	//	cout << "Your choice ? ";
	//	cin.ignore(); // Clear any remaining newline character
	//	getline(cin, choice);
	//	try
	//	{
	//		orderPointer = restaurantPointer->getIncomingOrder()->searchOrder(choice);
	//		if (orderPointer == nullptr)
	//			throw "Invalid Choice!";
	//		break;
	//	}
	//	catch (const char* msg)
	//	{
	//		cout << "Invalid Choice!" << endl;
	//		return;
	//	}

	//}

	//while (true)
	//{
	//	cout << "What would you like to update?" << endl;
	//	cout << "1. Order Status" << endl;
	//	cout << "2. Food Item" << endl;
	//	cout << "0. Exit" << endl;
	//	cout << "Your choice ? ";
	//	string choice;
	//	cin.ignore(); // Clear any remaining newline character
	//	getline(cin, choice);
	//	if (choice == "1")
	//	{
	//		updateOrderStatus(*orderPointer);
	//		break;
	//	}
	//	else if (choice == "2")
	//	{
	//		updateFoodItem();
	//		break;
	//	}
	//	else if (choice == "0")
	//	{
	//		break;
	//	}
	//	else
	//	{
	//		cout << "Invalid Choice!" << endl;
	//	}
	//}
}

void RestaurantStaff::updateFoodItem(/*FoodItem* foodItemPointer*/)
{
    FoodItem* foodItemPointer = nullptr;
    while (true)
    {
		string choice;

		cout << "What Food Item would you like to update?";
        restaurantPointer->getRestaurantMenuPointer()->printAllInOrder();
        cout << "Your choice ? ";
        cin.ignore(); // Clear any remaining newline character
        getline(cin, choice);
		try
        {
			foodItemPointer = restaurantPointer->getRestaurantMenuPointer()->searchNode(choice);
            if (foodItemPointer == nullptr)
				throw "Invalid Choice!";
			break;
		}
        catch (const char* msg)
        {
            cout << "Invalid Choice!" << endl;
            return;
        }
        
    }
    
    while (true)
    {
        cout << "What would you like to update?" << endl;
        cout << "1. Price" << endl;
        cout << "2. Availability" << endl;
        cout << "0. Exit" << endl;
        cout << "Your choice ? ";
        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a valid number." << endl;
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            continue; // Restart the loop
        }

        switch (choice)
        {
        case 1:
        {
            cout << "Enter new price: ";
            double newPrice;
            if (!(cin >> newPrice) || newPrice < 0) 
            {
                cout << "Invalid input for price. Please enter a valid number." << endl;
                cin.clear(); // Clear error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                continue; // Restart the loop
            }
            foodItemPointer->setFoodItemPrice(newPrice);
            cout << "Price updated successfully!" << endl;
            break;
        }

        case 2:
        {
            cout << "Enter new availability (True for available, False for not available): ";
            string newAvailabilityStr;
            getline(cin, newAvailabilityStr);

            if (newAvailabilityStr == "True" || newAvailabilityStr == "False")
            {
                bool newAvailability = (newAvailabilityStr == "True");
                foodItemPointer->setAvailability(newAvailability);
                cout << "Availability updated successfully!" << endl;
            }
            else
            {
                cout << "Invalid input for availability. Please enter 'True' or 'False'." << endl;
            }
            break;
        }

        case 0:
            return;

        default:
            cout << "Invalid input" << endl;
            break;
        }
    }
}

void RestaurantStaff::addFoodItem()
{
    string name, description, category;
    double price;

    cout << "Enter the name of the new food item: ";
    cin.ignore(); // Clear any remaining newline character
    getline(cin, name);

    cout << "Enter the description of the new food item: ";
    getline(cin, description);

    cout << "Enter the category of the new food item: ";
    getline(cin, category);

    while (true) 
    {
        cout << "Enter the price of the new food item: ";
        if (cin >> price && price >= 0)
        {
            break; // Input is valid, exit the loop
        }
        else 
        {
            cout << "Invalid input for price. Please enter a valid positive number." << endl;
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        }
    }

    // TODO: INPUT VALIDATION WTF.
    bool isAvailable = true;
    FoodItem newFoodItem(name, description, category, isAvailable, price);

    // Add the new food item to the restaurant's menu
    restaurantPointer->getRestaurantMenuPointer()->insertNode(newFoodItem);

    cout << "New food item added to the menu!" << endl;
}




string RestaurantStaff::getEmail()
{
    return email;
}

string RestaurantStaff::getPasswordHash()
{
    return passwordHash;
}

void RestaurantStaff::setPasswordHash(string newPasswordHash)
{
    passwordHash = newPasswordHash;
}

string RestaurantStaff::getRestaurantName()
{
	return restaurantName;
}

void RestaurantStaff::setRestaurantName(string aRestaurantName)
{
	restaurantName = aRestaurantName;
}

void RestaurantStaff::setRestaurantPointer(Restaurant* aRestaurantPointer)
{
	restaurantPointer = aRestaurantPointer;
}

Restaurant* RestaurantStaff::getRestaurantPointer()
{
	return restaurantPointer;
}
#include "RestaurantStaff.h"

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

void RestaurantStaff::updateFoodItem(FoodItem* foodItemPointer)
{
    while (true)
    {
        cout << "What would you like to update?" << endl;
        cout << "1. Price" << endl;
        cout << "2. Availability" << endl;
        cout << "3. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter new price: ";
            double newPrice;
            cin >> newPrice;
            foodItemPointer->setFoodItemPrice(newPrice);
            cout << "Price updated successfully!" << endl;
            break;

        case 2:
            cout << "Enter new availability (1 for available, 0 for not available): ";
            int newAvailability; // Use an integer to represent boolean (1 for true, 0 for false)
            cin >> newAvailability;
            if (newAvailability == 0 || newAvailability == 1) {
                foodItemPointer->setAvailability(newAvailability);
                cout << "Availability updated successfully!" << endl;
            }
            else {
                cout << "Invalid input for availability. Please enter 0 or 1." << endl;
            }
            break;

        case 3:
            return;

        default:
            cout << "Invalid input" << endl;
            break;
        }
    }
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
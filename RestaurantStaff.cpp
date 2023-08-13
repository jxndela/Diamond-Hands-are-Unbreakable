#include "RestaurantStaff.h"

// Constructor
RestaurantStaff::RestaurantStaff()
{

}

RestaurantStaff::RestaurantStaff(string aEmail, string aPasswordhash, Restaurant* aRestaurantPointer)
{
    email = aEmail;
    passwordHash = aPasswordhash;
    aRestaurantPointer = aRestaurantPointer;
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

void RestaurantStaff::updateFoodItem(FoodItem foodItem)
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
            foodItem.setFoodItemPrice(newPrice);
            break;

        case 2:
            cout << "Enter new availability: ";
            bool newAvailability;
            cin >> newAvailability;
            foodItem.setAvailability(newAvailability);
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
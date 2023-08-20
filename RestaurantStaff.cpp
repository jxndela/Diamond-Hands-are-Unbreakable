/*
 * T03 Jonathan Ho S10246045 Ong Jun Jie S10240117
 * Done by Ong Jun Jie
 */
#include "RestaurantStaff.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <chrono>
#include <cstring>
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

string RestaurantStaff::getEmail()
{
    return email;
}

string RestaurantStaff::getPasswordHash()
{
    return passwordHash;
}

string RestaurantStaff::getRestaurantName()
{
    return restaurantName;
}

Restaurant* RestaurantStaff::getRestaurantPointer()
{
    return restaurantPointer;
}

void RestaurantStaff::setRestaurantName(string aRestaurantName)
{
    restaurantName = aRestaurantName;
}

void RestaurantStaff::setRestaurantPointer(Restaurant* aRestaurantPointer)
{
    restaurantPointer = aRestaurantPointer;
}

void RestaurantStaff::setPasswordHash(string newPasswordHash)
{
    passwordHash = newPasswordHash;
}


void RestaurantStaff::viewAllOrders()
{
    restaurantPointer->getIncomingOrder()->printQueue();
}

void RestaurantStaff::viewOrderAndCustomerInfo(Order aOrder)
{
    aOrder.printOrderInformation();
}

void RestaurantStaff::updateOrderStatus(Order& aOrder)
{
    aOrder.printOrderInformation();
    cout << "First Order has been set to completed" << endl;
    aOrder.setOrderStatusComplete();
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

void RestaurantStaff::generateReport()
{
    while (true)
    {
        string input;
		int choice;
            
		cout << "What report would you like to generate?" << endl;
		cout << "1. Total Sales for the last week" << endl;
		cout << "2. Total Sales for the last month" << endl;
		cout << "3. Total Sales for all time" << endl;
		cout << "0. Exit" << endl;
		cout << "Your choice ? ";
        cin.ignore();
		getline(cin, input);
		choice = stoi(input);
        switch (choice)
        {
        case 1: case 2: case 3:
        {
            loadPastOrders(input);
            return;
        }

        case 0:
            return;

        default:
            cout << "Invalid input" << endl;
            break;
        }
    }
}

void RestaurantStaff::loadPastOrders(string date)
{
    ifstream inFile("pastorders.txt");
    if (!inFile.is_open())
    {
        // no file exists
        cout << "No orders exist!" << endl;
        return;
    }

    string timestamp, restaurantName, customerName, totalCost, aString, line;
    int count = 0;
    double totalRevenue = 0;

    // Get the current time
    auto currentTime = chrono::system_clock::now();
    time_t currentTimeT = chrono::system_clock::to_time_t(currentTime);

    while (getline(inFile, line))
    {
        stringstream ss(line);
        getline(ss, timestamp, ',');
        getline(ss, restaurantName, ',');

        if (restaurantName != restaurantPointer->getRestaurantName())
        {
            continue;
        }

        getline(ss, customerName, ',');
        getline(ss, totalCost);

        // Parse the order's timestamp using std::get_time
        tm orderTime = {};
        istringstream timestampStream(timestamp);
        timestampStream >> get_time(&orderTime, "%Y-%m-%d %H:%M:%S");
        time_t orderTimeT = mktime(&orderTime);

        // Calculate the difference in seconds between current time and order time
        double timeDifference = difftime(currentTimeT, orderTimeT);

        if (date == "1" && timeDifference <= 7 * 24 * 60 * 60 && timeDifference >= 0) {
            cout << "Order made on " << timestamp << " by " << customerName << " for $" << totalCost << endl;
            totalRevenue += stod(totalCost);
            count++;
        }
        else if (date == "2" && timeDifference <= 30 * 24 * 60 * 60 && timeDifference >= 0) {
            cout << "Order made on " << timestamp << " by " << customerName << " for $" << totalCost << endl;
            totalRevenue += stod(totalCost);
            count++;
        }
        else if (date == "3") {
            cout << "Order made on " << timestamp << " by " << customerName << " for $" << totalCost << endl;
            totalRevenue += stod(totalCost);
            count++;
        }
    }

    cout << "=====================" << endl;
    cout << "Total orders : " << count << endl;
    cout << "Total revenue : $" << totalRevenue << endl;
    inFile.close();
    return;
}



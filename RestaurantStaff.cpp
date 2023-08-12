#include "RestaurantStaff.h"

// Constructor
RestaurantStaff::RestaurantStaff()
{

}

RestaurantStaff::RestaurantStaff(Restaurant* aRestaurantPointer)
{
	aRestaurantPointer = aRestaurantPointer;
}


RestaurantStaff::~RestaurantStaff()
{
}

void RestaurantStaff::viewAllOrders()
{
	cout << "VIEWING ALL ORDERS" << endl;
	restaurantPointer->getIncomingOrder()->printQueue();
}


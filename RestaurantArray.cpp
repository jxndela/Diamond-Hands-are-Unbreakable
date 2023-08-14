#include "RestaurantArray.h"

RestaurantArray::RestaurantArray()
{
	readRestaurantFile();
}
RestaurantArray::~RestaurantArray(){}

void RestaurantArray::addRestaurant(Restaurant& aRestaurant, int& aIndexPosition)
{
	restaurants[aIndexPosition] = aRestaurant;
	numberOfRestaurants++;
}

Restaurant* RestaurantArray::getRestaurant(int aIndexPosition)
{
	return &restaurants[aIndexPosition];
}



void RestaurantArray::readRestaurantFile()
{
	// Open file restaurant.txt
	ifstream inFile("restaurant.txt");
	// If not open, then create a new one
	if (!inFile.is_open())
	{
		// Create the file if it doesn't exist
		ofstream newFile("restaurant.txt");
		newFile.close();

		// Try opening the newly created file
		inFile.open("restaurant.txt");
		if (!inFile.is_open())
		{
			return; // Still unable to open the file
		}
	}

	string restaurantName, postalCodeString;
	int postalCode;
	string foodItemName, description, category, priceString;
	double price;

	string aString;
	string line;
	int indexPosition = 0;

	while (getline(inFile, line))
	{
		stringstream ss(line);
		string firstWord;
		getline(ss, firstWord, ',');
		// If restaurant
		if (firstWord == "Restaurant")
		{
			getline(ss, restaurantName, ',');
			getline(ss, postalCodeString);
			postalCode = stoi(postalCodeString);
			// Create the new restaurant
			Restaurant newRestaurant(restaurantName, postalCode);
			// Add it it this restaurant array
			addRestaurant(newRestaurant, indexPosition);
			indexPosition++;
		}
		else if (firstWord == "FoodItem")
		{
			getline(ss, foodItemName, ',');
			getline(ss, description, ',');
			getline(ss, category, ',');
			getline(ss, priceString);
			price = stod(priceString);
			// Create new food item
			FoodItem newFoodItem(foodItemName, description, category, price);
			// Add new food item
			restaurants[indexPosition].restaurantMenuPointer()->insertNode(newFoodItem);
		}
	}
}

void RestaurantArray::printRestaurants()
{
	for (int i = 1;i < numberOfRestaurants + 1; i++)
	{
		cout << i << ". " << restaurants[i-1].getRestaurantName() << "\t"
		<< restaurants[i-1].getRestaurantName() << endl;
	}
}





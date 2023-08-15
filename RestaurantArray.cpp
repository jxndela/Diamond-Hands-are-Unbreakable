#include "RestaurantArray.h"

RestaurantArray::RestaurantArray()
{
	// Read the text file.
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

int RestaurantArray::getNumberOfRestaurants()
{
	return numberOfRestaurants;
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
	// Open file foodItems.txt
	ifstream inFile2("foodItem.txt");
	// If not open, then create a new one
	if (!inFile2.is_open())
	{
		// Create the file if it doesn't exist
		ofstream newFile2("foodItem.txt");
		newFile2.close();

		// Try opening the newly created file
		inFile2.open("foodItem.txt");
		if (!inFile2.is_open())
		{
			return; // Still unable to open the file
		}
	}
	// Create temporary variables to store the individual values
	string restaurantName, postalCodeString;
	int postalCode;
	string foodItemName, description, category,isAvailableString, priceString;
	double price;
	bool isAvailable;
	// Create temporary variabels to store string and line, as well as counter for index
	string aString;
	string line;
	string indexPositionString;
	int indexPosition = 0;

	while (getline(inFile, line))
	{
		stringstream ss(line);
		// Next value will be as follows followed by a comma
		getline(ss, restaurantName, ',');
		getline(ss, postalCodeString);
		postalCode = stoi(postalCodeString);
		// Create the new restaurant
		Restaurant newRestaurant(restaurantName, postalCode);
		// Add it it this restaurant array
		addRestaurant(newRestaurant, indexPosition);
		indexPosition++;
	}
	while (getline(inFile2, line))
	{
		stringstream ss(line);
		// Next value will be as follows followed by a comma

		getline(ss, indexPositionString, ',');
		indexPosition = stoi(indexPositionString);
		getline(ss, foodItemName, ',');
		getline(ss, description, ',');
		getline(ss, category, ',');
		getline(ss, isAvailableString, ',');
		if (isAvailableString == "true") isAvailable = true;
		if (isAvailableString == "false") isAvailable = false;
		getline(ss, priceString);
		price = stod(priceString);
		// Create the new foodItem
		FoodItem newFoodItem(foodItemName, description, category, isAvailable, price);
		Restaurant* restaurantPointer = &restaurants[indexPosition];
		restaurantPointer->getRestaurantMenuPointer()->insertNode(newFoodItem);
	}
}

void RestaurantArray::writeRestaurantFile()
{
	ofstream outFile("restaurant.txt");

	// If no file exists, create a new restaurant.txt file
	if (!outFile.is_open())
	{
		ofstream newFile("restaurant.txt");
		newFile.close();
		outFile.open("restaurant.txt");
	}

	// File exists, lets write for each restaurant
	for (int i = 0; i < numberOfRestaurants - 1;i++ )
	{
		// Print out information about the restaurant with restaurant header
		outFile << "Restaurant," << restaurants[i].getRestaurantName() << ","
		<< restaurants[i].getPostalCode() << endl;
		// Access the menu of the restaurant above
		FoodItemAVL* menu = restaurants[i].getRestaurantMenuPointer();
		// 
	}
}

void RestaurantArray::printRestaurants()
{
	for (int i = 1;i < numberOfRestaurants + 1; i++)
	{
		cout << i << ". " << restaurants[i-1].getRestaurantName() << "\t"
		<< restaurants[i-1].getPostalCode() << endl;
	}
}

void RestaurantArray::writeFoodItemsAVL(ofstream& aOutFile, AVLNode* aNode)
{
	// End if the restaurant does not have any food items
	if (aNode == nullptr)
		return;

	// Write food item recursively
	aOutFile << "FoodItem," << aNode->foodItem.getName() << ","
		<< aNode->foodItem.getFoodDescription() << ","
		<< aNode->foodItem.getCategory() << ","
		<< aNode->foodItem.getPrice() << ","
		<< aNode->foodItem.getAvailability() << endl;

	writeFoodItemsAVL(aOutFile, aNode->left);
	writeFoodItemsAVL(aOutFile, aNode->right);
}





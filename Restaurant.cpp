#include "Restaurant.h"

// Default Constructor
Restaurant::Restaurant()
{
	restaurantName = "SUCK MY COCK";
	postalCode = 123456;
	incomingOrder = nullptr;
	restaurantMenu;
}

// Parameterized Constructor
Restaurant::Restaurant(string aRestaurantName, int aPostalCode)
{
	restaurantName = aRestaurantName;
	postalCode = aPostalCode;
	restaurantMenu;
	incomingOrder = new OrderQueue;
}

// Destructor
Restaurant::~Restaurant()
{
}

// Returns restaurant name
// Pre : ~
// Post: Restaurant name
string Restaurant::getRestaurantName()
{
	return restaurantName;
}

// Returns postalCode
// Pre : ~
// Post: postalCode
int Restaurant::getPostalCode()
{
	return postalCode;
}

void Restaurant::printMenu()
{
	cout << "PRINTING MENU" << endl
		<< "=============" << endl;
	restaurantMenu.printInOrder();
	cout <<"=============" << endl; 
}


// Constructor
RestaurantArray::RestaurantArray()
{
	// Read the text file.
	readRestaurantFile();
}

// Destructor
RestaurantArray::~RestaurantArray()
{
	// Save before destroying.
	writeRestaurantFile();
	writeFoodItemsAVL();
}

// Get method - no. of restaurants
int RestaurantArray::getNumberOfRestaurants()
{
	return numberOfRestaurants;
}

// Get method - Pointer of specific restaurant
Restaurant* RestaurantArray::getRestaurant(int aIndexPosition)
{
	return &allRestaurants[aIndexPosition];
}

// Get method - Pointer to restaurants[MAX_RESTAURANTS]
Restaurant* RestaurantArray::GetAllRestaurant()
{

	return allRestaurants;

}

// Add new restaurant add a specific index position
void RestaurantArray::addRestaurant(Restaurant& aRestaurant, int& aIndexPosition)
{
	allRestaurants[aIndexPosition] = aRestaurant;
	numberOfRestaurants++;
}

// Print Restaurant
void RestaurantArray::printRestaurants()
{
	for (int i = 1; i < numberOfRestaurants + 1; i++)
	{
		std::cout << i << ". " << allRestaurants[i - 1].getRestaurantName() << "\t"
			<< allRestaurants[i - 1].getPostalCode() << endl;
	}
}


// Read .txt file
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
	string foodItemName, description, category, isAvailableString, priceString;
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
		Restaurant* restaurantPointer = &allRestaurants[indexPosition];
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
	for (int i = 0; i < numberOfRestaurants; i++)
	{
		// Print out information about the restaurant with restaurant header
		outFile << allRestaurants[i].getRestaurantName() << ","
			<< allRestaurants[i].getPostalCode() << endl;
	}
	outFile.close();
}

void RestaurantArray::writeFoodItemsRecursive(ofstream& aOutFile, AVLNode* aNode, int& aIndexPosition)
{
	// End if the restaurant does not have any food items
	if (aNode == nullptr)
		return;

	string availabilityString;
	if (aNode->foodItem.getAvailability() == true)
		availabilityString = "true";
	if (aNode->foodItem.getAvailability() == false)
		availabilityString = "false";

	// Write food item recursively
	aOutFile << aIndexPosition << ","
		<< aNode->foodItem.getName() << ","
		<< aNode->foodItem.getFoodDescription() << ","
		<< aNode->foodItem.getCategory() << ","
		<< availabilityString << ","
		<< aNode->foodItem.getPrice() << endl;

	writeFoodItemsRecursive(aOutFile, aNode->left, aIndexPosition);
	writeFoodItemsRecursive(aOutFile, aNode->right, aIndexPosition);
}

void RestaurantArray::writeFoodItemsAVL()
{
	ofstream outFile("foodItem.txt");

	// If no file exists, create a new restaurant.txt file
	if (!outFile.is_open())
	{
		ofstream newFile("foodItem.txt");
		newFile.close();
		outFile.open("foodItem.txt");
	}
	for (int i = 0; i < numberOfRestaurants; i++)
	{
		AVLNode* menuPointer = getRestaurant(i)->getRestaurantMenuPointer()->getRoot();
		writeFoodItemsRecursive(outFile, menuPointer, i);
	}
}



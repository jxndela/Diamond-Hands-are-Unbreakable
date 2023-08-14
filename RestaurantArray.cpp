#include "RestaurantArray.h"

RestaurantArray::RestaurantArray() {}
RestaurantArray::~RestaurantArray(){}

void RestaurantArray::addRestaurant(Restaurant& aRestaurant, int& aIndexPosition)
{
	restaurants[aIndexPosition] = aRestaurant;
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
	// Initialize a stack
	RestaurantStack contextStack;
	// Temp string to store value
	string line;
	int indexPosition = 0;
	// While there are lines in file
	while (getline(inFile, line) && indexPosition < MAX_RESTAURANTS) {
		istringstream iss(line);
		char delimiter;
		string token;

		// Process each token using commas and parentheses as delimiters
		while (iss >> delimiter >> token >> delimiter) {
			if (delimiter == '(') {
				// Start of a new context, push the context type onto the stack
				contextStack.push(token);
			}
			else if (delimiter == ')') {
				// End of the current context, pop the context type from the stack
				contextStack.pop();
			}
			else {
				// Process data based on the current context
				if (!contextStack.isEmpty()) {
					std::string contextType = contextStack.getTop();
					// Process restaurant data
					if (contextType == "Restaurant")
					{
						string restaurantName, postalCodeString;
						int postalCode;
						// Extract name and postal code string
						getline(iss, restaurantName, ',');
						getline(iss, postalCodeString, ',');
						postalCode = stoi(postalCodeString);

						// Create the new restaurant
						Restaurant newRestaurant(restaurantName, postalCode);
						// Add it it this restaurant array
						addRestaurant(newRestaurant, indexPosition);
					}
					// Process food item data
					else if (contextType == "FoodItem")
					{
						// repeat but like for food
						string foodItemName, description, category, priceString;
						double price;
						getline(iss, foodItemName, ',');
						getline(iss, description, ',');
						getline(iss, category, ',');
						getline(iss, priceString, ',');
						// stod is string to double
						price = stod(priceString);
						// Create new food item
						FoodItem newFoodItem(foodItemName, description, category, price);
						// Add new food item
						restaurants[indexPosition].restaurantMenuPointer()->insertNode(newFoodItem);
					}
					// Finish processing part of contextt information
				}
				// Finish checking empty
			}
			// Finish processing inside of ( )
		}
		// Exit while loop for 1 line
	}
	// Exit finishhing whole txt file or too many restaurants
}

void RestaurantArray::printRestaurants()
{
	int counter = 1;
	for (Restaurant a : restaurants)
	{
		cout << counter << ". " << a.getRestaurantName() << "\t" << a.getPostalCode() << endl;
		counter++;
	}
}

// Consturctor
// Top is at -1 as index starts at 0
RestaurantStack::RestaurantStack()
{
	top = -1;
}

// Destructor
// If not empty pop everything
RestaurantStack::~RestaurantStack()
{
	if (!isEmpty())
	{
		pop();
	}
}

// Push a new item to the top of stack
void RestaurantStack::push(string& value)
{
	// If not full
	if (top < STACK_MAX_SIZE - 1)
	{
		top++;
		stack[top] = value;
	}
	else
	{
		cout << "Stack is full cannot push" << endl;
	}
}

// Pop whatever is on top
void RestaurantStack::pop()
{
	if (!isEmpty())
	{
		top--;
	}
	else
	{
		cout << "Cannot pop empty Stack" << endl;
	}
}

// Get string value of whatever is on top
string RestaurantStack::getTop()
{
	if (!isEmpty())
	{
		return stack[top];
	}
	else
		return "";
}

bool RestaurantStack::isEmpty()
{
	return top == -1;
}









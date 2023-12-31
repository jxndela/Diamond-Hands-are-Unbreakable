#include "OrderQueue.h"
#include <chrono>
// Default constructor
OrderQueue::OrderQueue()
{
	frontNode = nullptr;
	backNode = nullptr;
	size = 0;
}

// Destructor
OrderQueue::~OrderQueue()
{
}

// Check for empty q
bool OrderQueue::isEmpty()
{
	return size == 0;
}

// Get item from front of q
// Pre : Order should exist
// Post: Order will be stored in aOrder
void OrderQueue::getFront(Order& aOrder)
{
	if (!isEmpty())
		aOrder = *(frontNode->orderPointer);
}

// Get the front node
OrderNode* OrderQueue::getFrontOrderNode()
{
	return frontNode;
}

// Get item from back of q
// Pre : Order should exist
// Post: Order will be stored in a0rder
void OrderQueue::getBack(Order& aOrder)
{
	if (!isEmpty())
		aOrder = *(backNode->orderPointer);
}

// Get number of orders in queue
int OrderQueue::getNumberOfOrders()
{
	return size;
}

// Print Queue;
// Pre: Queue should exist
// Post: Prints all the order id that is inside with numbers
void OrderQueue::printQueue()
{
	if (isEmpty())
	{
		cout << "Cannot print out empty Queue!" << endl;
		return;
	}

	cout << "Printing all orders in queue..." << endl;
	// Create temporary node pointer set to front
	// Create a counter to show appropriate number starting at 1
	OrderNode* current = frontNode;
	int counter = 1;
	// Iterate throught the queue
	/*while (current != nullptr)
	{
		current->orderPointer->printOrderInformation();
		current = current->next;
	}*/

	for (int i = 1; current != nullptr; i++)
	{
		cout << "Order Number: " << i << endl;
		current->orderPointer->printOrderInformation();
		current = current->next;
		counter++;
	}
}

// Enqueue (add) item to back of q
// Pre : ~ 
// Post: Added to q
bool OrderQueue::enqueue(Order* aOrderPointer)
{
	// Create temp node
	OrderNode* tempNode = new OrderNode();
	tempNode->orderPointer = aOrderPointer;
	tempNode->next = nullptr;
	// If empty then frontNode point to tempNode
	if (isEmpty())
	{
		frontNode = tempNode;
	}
	// Else then the front does not change
	else
	{
		backNode->next = tempNode;
	}
	// Set the backNode to the tempNode
	backNode = tempNode;
	size++;
	return true;
}

// Dequeue (remove) item at front of q
// Pre : Order at frontNode must exist
// Post: Order at front is removed
bool OrderQueue::dequeue()
{
	// Check if queue is empty, exit if necessary
	if (isEmpty())
	{
		cout << "Cannot dequeue empty order queue! " << endl;
		return false;
	}

	
	// Create a temporary pointer
	OrderNode* tempPointer = frontNode;

	// Check if it is last item in queue
	if (frontNode == backNode)
	{
		// Set to null as nothing will be left
		frontNode = nullptr;
		backNode = nullptr;
	}
	// Else the new frontNode is the second in line
	else
	{
		frontNode = frontNode->next;
	}

	// Delete any pointers associated with original front node
	tempPointer->next = nullptr;
	delete tempPointer;

	// Reduce size and return true
	size--;
	return true;
}

void OrderQueue::saveOrderToFile()
{
    // get current time and date
    auto currentTime = chrono::system_clock::now();
    time_t currentTimeT = chrono::system_clock::to_time_t(currentTime);

    char currentTimeStr[100];
    tm timeInfo;
    localtime_s(&timeInfo, &currentTimeT);
    strftime(currentTimeStr, sizeof(currentTimeStr), "%Y-%m-%d %H:%M:%S", &timeInfo);

    // append to file
    ofstream outFile("pastorders.txt", ios_base::app); // Open in append mode
    outFile << currentTimeStr << ","
        << frontNode->orderPointer->getRestaurantPointer()->getRestaurantName() << ","
        << frontNode->orderPointer->getCustomerName() << ","
        << frontNode->orderPointer->totalCost()
        << endl;

	// Close the file
    outFile.close();
}



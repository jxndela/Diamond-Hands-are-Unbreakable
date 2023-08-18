#include "OrderQueue.h"

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
		cout << "Cannot print out empty Queue you ding dong!" << endl;
		return;
	}

	cout << "Printing all orders in queue..." << endl;

	// Create temporary node pointer set to front
	// Create a counter to show appropriate number starting at 1
	OrderNode* current = frontNode;
	int counter = 1;

	// Iterate throught the queue
	while (current != nullptr)
	{
		cout << "HAAHAH" << endl;
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
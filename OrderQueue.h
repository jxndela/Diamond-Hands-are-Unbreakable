#pragma once
#include <string>
#include <iostream>
#include "Order.h"

using namespace std;

struct orderNode
{
	Order* orderPointer;
	orderNode* next;
};

class OrderQueue
{
private:
	orderNode* frontNode;
	orderNode* backNode;
	int size;

public:
	// Default constructor
	OrderQueue();

	// Destructor
	~OrderQueue();

	// Check for empty q
	bool isEmpty();

	// Get item from front of q
	// Pre : Order should exist
	// Post: Order will be stored in aOrder
	void getFront(Order& aOrder);

	// Get item from back of q
	// Pre : Order should exist
	// Post: Order will be stored in a0rder
	void getBack(Order& aOrder);

	// Get number of orders in queue
	int getNumberOfOrders();

	// Print Queue;
	void printQueue();

	// Enqueue (add) item to back of q
	// Pre : ~ 
	// Post: Added to q
	bool enqueue(Order* aOrderPointer);

	// Dequeue (remove) item at front of q
	// Pre : Order at frontNode must exist
	// Post: Order at front is removed
	bool dequeue();

};


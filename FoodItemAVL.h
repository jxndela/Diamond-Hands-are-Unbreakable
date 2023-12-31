#pragma once
#include <iostream>
#include <string>
#include "FoodItem.h"

// Forward declaration
class FoodItem;

using namespace std;

// Implement the AVL Nodes that we will be using
struct AVLNode
{
    FoodItem foodItem;     // AVL 
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
    int height = 0;
};

// Purpose of AVL Tree structure - 
// We want the tree to automatically balance based on the name of food
class FoodItemAVL
{
private:
    // Root of tree. God almighty
    AVLNode* root;

    // Get the height of the node in the AVL Tree
    // Pre : Node exits
    // Post: Positive int value
    int getHeight(AVLNode* aNode);

    // Determine which way a node should rotate
    // Pre : Need a valid node
    // Post: Gets the height of the left node - the right node
    int getBalanceFactor(AVLNode* aNode);

    // Get the fooditem address so that we can retreive info
    // Pre : Need a valid node
    // Post: Returns addrress
    FoodItem* getFoodItemPointer(AVLNode* aNode);

    // Rotate node right
    // Pre : pivot node
    // Post: rotated right
    // Let y represent the root node
    AVLNode* rotateRight(AVLNode* y);

    // Rotate node left
    // Pre : pivot node
    // Post: rotated left
    // Let x represent the root node
    AVLNode* rotateLeft(AVLNode* x);

    // Rotate until happy lor must be balance according to balance factor
    // Pre : pivot
    // Post: BALANCE
    AVLNode* balanceNode(AVLNode* aNode);

    // Recursively insert a node in the AVL Tree
    // Pre : Need pointer aNode to inform where to insert
    //       Need existing food item in order to create a node
    // Post: Recursively calls itself in order to insert a new node 
    //       containing aFoodItem into the correct position
    AVLNode* insertNodeRecursive(AVLNode* aNode, FoodItem& aFoodItem);

    // Recursively search for a specific node containing the fooditem with
    // corresponding foodItemName
    // Pre : Need the a starting node 
    // Post: returns the AVL node pointer which contains the fooditem
    //       returns nullptr otherwise
    AVLNode* searchNodeRecursive(AVLNode* aNode, string& foodItemName);

    // Recursively searches for a specific node containing the fooditem with 
    // corresponding foodItemName. Afterwhich, it will delete the node
    // Pre : Need the starting node
    // Post: Return nullptr if succesful
    AVLNode* deleteNodeRecursive(AVLNode* aNode, const string& foodItemName);

    // recurisive print function 
    void printInOrderRecursive(AVLNode* aNode);

    // recurisive print function (all items)
	void printAllInOrderRecursive(AVLNode* aNode);

    // recursive add fooditem into array (all items)
    void addFoodIntoArrayRecursive(AVLNode* aNode, FoodItem* aFoodItemArray[], int& aIndexPosition)
    {
        // base case
        if (aNode == nullptr)
            return;
        // Recusively add the left child
        addFoodIntoArrayRecursive(aNode->left, aFoodItemArray, aIndexPosition);

        // Add the foodItem pointer in the current node into the array based on index position
        aFoodItemArray[aIndexPosition] = &aNode->foodItem;
        aIndexPosition++;

        // Recusively add the right child
        addFoodIntoArrayRecursive(aNode->right, aFoodItemArray, aIndexPosition);
    }


public:
    // Constructor
    FoodItemAVL();

    // Destructor
    ~FoodItemAVL();

    // Get the root
    AVLNode* getRoot();

    // Insert node into the AVL tree
    // Pre : Tree must exist i guess
    // Post: The node will be inserted into the tree int the correct position
    //       It will automatically correct the structure of the tree if unbalanced
    void insertNode(FoodItem aFoodItem);

    // Search for an item by the food item Name
    // Pre : Not a null AVL Tree
    // Post: Returns the address of the foodItem stored within the tree
    FoodItem* searchNode(string& foodItemName);

    // Print in alphabetical order (A-Z)
    // Pre : Not a null AVL Tree
    // Post: Prints the full item menu of the restaurant in which the AVL tree belongs to
    void printInOrder();

    // Print in alphabetical order (A-Z) (all items)
    // Pre : Not a null AVL Tree
    // Post: Prints the full item menu of the restaurant in which the AVL tree belongs to
    void printAllInOrder();

    // Delete a node inside AVL Tree by searching for its name
    // Pre : Not a null AVL Tree 
    // Post: Returns true if the Node has been successfully delted & tree auto balances
    //       Returns false if unable to find node
    bool deleteNode(string& foodItemName);

    // Add food into array
    void addFoodIntoArray(FoodItem* aFoodItemArray[], int& aIndexPosition);
};


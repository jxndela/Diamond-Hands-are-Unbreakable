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



public:
    // Constructor
    FoodItemAVL();

    // Destructor
    ~FoodItemAVL();

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

    // Delete a node inside AVL Tree by searching for its name
    // Pre : Not a null AVL Tree 
    // Post: Returns true if the Node has been successfully delted & tree auto balances
    //       Returns false if unable to find node
    bool deleteNode(string& foodItemName);
    
    // Delete whole tree
    void deleteTree(AVLNode* aNode);

    AVLNode* getRoot()
    {
        return root;
    }
};


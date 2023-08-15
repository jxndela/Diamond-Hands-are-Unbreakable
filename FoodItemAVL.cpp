#include "FoodItemAVL.h"
using namespace std;

// Constructor
FoodItemAVL::FoodItemAVL()
{
    // initalize attributes
    root = nullptr;
}

// Destructor
FoodItemAVL::~FoodItemAVL()
{
    // Recursively delete everything
    deleteTree(root);
}

// Get the height of the node in the AVL Tree
// Pre : Node exits
// Post: Positive int value
int FoodItemAVL::getHeight(AVLNode* aNode)
{
    // Return 0 if empty
    if (aNode == nullptr)
        return 0;
    return aNode->height;
}

// Determine which way a node should rotate
// Pre : Need a valid node
// Post: Gets the height of the left node - the right node
int FoodItemAVL::getBalanceFactor(AVLNode* aNode)
{
    if (aNode == nullptr)
        return 0;
    // Get the height of left node, and right node
    // Return the difference.
    return getHeight(aNode->left) - getHeight(aNode->right);
}

FoodItem* FoodItemAVL::getFoodItemPointer(AVLNode* aNode)
{
    if (aNode == nullptr)
        return nullptr;

    return &(aNode->foodItem);
}

// Rotate node right
// Pre : pivot node
// Post: rotated right
// Let y represent the root node
AVLNode* FoodItemAVL::rotateRight(AVLNode* y)
{
    // x is left child of y 
    AVLNode* x = y->left; 
    // z is right child of x
    AVLNode* z = x->right;

    // Right Child of x now points to Y
    x->right = y;
    // Left Child of Y now points to Z 
    y->left = z;

    // Update heights of y and x after the rotation. 
    // height of z still remains the same
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Return x as the root node
    return x;
}

// Rotate node left
// Pre : pivot node
// Post: rotated left
// Let x represent the root node
AVLNode* FoodItemAVL::rotateLeft(AVLNode* x)
{
    // y is right child of x
    AVLNode* y = x->right;
    // z is Left child of y
    AVLNode* z = y->left;

    // Left child of Y now points to X
    y->left = x;
    // Right child of X now points to Z
    x->right = z;

    // update heights of x and y
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // return y as the root node
    return y;
}

// Rotate until happy lor must be balance according to balance factor
// Pre : pivot
// Post: BALANCE
AVLNode* FoodItemAVL::balanceNode(AVLNode* aNode)
{
   // Get balance to see if the tree is left heavy or right heavy
    int balance = getBalanceFactor(aNode);

    // LEFT HEAVY
    if (balance > 1)
    {
        // LEFT LEFT HEAVY
        // CORRECT WITH RIGHT ROTATION
        if (getBalanceFactor(aNode->left) >= 0)
            return rotateRight(aNode);

        // Left Right case
        // CORRECT WITH LEFT RIGHT DOUBLE ROTATION
        else
        {
            aNode->left = rotateLeft(aNode->left);
            return rotateRight(aNode);
        }
    }

    // RIGHT HEAVY
    if (balance < -1)
    {
        // RIGHT RIGHT HEAVY 
        // CORRECT WITH LEFT ROTATION
        if (getBalanceFactor(aNode->right) <= 0)
            return rotateLeft(aNode);

        // RIGHT LEFT HEAVY
        // CORRECT WITH RIGHT LEFT DOUBLE ROTATION
        else
        {
            aNode->right = rotateRight(aNode->right);
            return rotateLeft(aNode);
        }
    }
    // RETURN THE NEW POSITION OF INPUT NODE
    return aNode;
}

// Recursively insert a node in the AVL Tree
// Pre : Need pointer aNode to inform where to insert
//       Need existing food item in order to create a node
// Post: Recursively calls itself in order to insert a new node 
//       containing aFoodItem into the correct position
AVLNode* FoodItemAVL::insertNodeRecursive(AVLNode* aNode, FoodItem& aFoodItem)
{
    // Check if the current node is null
    if (aNode == nullptr)
    {
        // Create a new node and initialize its properties
        AVLNode* newNode = (new AVLNode);
        newNode->foodItem = aFoodItem;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 1; // Initialize height as 1 for the new node
        cout << aFoodItem.getName() << " node has been created" << endl;
        cout << root << endl;
        return newNode; // Return the newly created node
        
    }
    
    // Compare the food item's name with the current node's food item's name
    if (aFoodItem.getName() < aNode->foodItem.getName())
        // If the new food item's name is less, recursively insert on the left subtree
        aNode->left = insertNodeRecursive(aNode->left, aFoodItem);
    else if (aFoodItem.getName() > aNode->foodItem.getName())
        // If the new food item's name is greater, recursively insert on the right subtree
        aNode->right = insertNodeRecursive(aNode->right, aFoodItem);
    else
        return aNode; // Duplicate items are not allowed, return the current node

    // Update the height of the current node after insertion
    aNode->height = 1 + max(getHeight(aNode->left), getHeight(aNode->right));
    // Rebalance the tree if necessary and return the updated node
    return balanceNode(aNode);
}

// Recursively search for a specific node containing the fooditem with
// corresponding foodItemName
// Pre : Need the a starting node 
// Post: returns the AVL node pointer which contains the fooditem
//       returns nullptr otherwise
AVLNode* FoodItemAVL::searchNodeRecursive(AVLNode* aNode, string& itemName)
{
    // Check if the current node is null or has the desired item name
    if (aNode == nullptr || aNode->foodItem.getName() == itemName)
        return aNode; // Return the current node (nullptr if not found or matching)

    // Compare the desired item name with the current node's food item's name
    if (itemName < aNode->foodItem.getName())
        // If the desired item name is smaller, search in the left subtree
        return searchNodeRecursive(aNode->left, itemName);
    else
        // If the desired item name is greater, search in the right subtree
        return searchNodeRecursive(aNode->right, itemName);
}

// Recursively searches for a specific node containing the fooditem with 
// corresponding foodItemName. Afterwhich, it will delete the node
// Pre : Need the starting node
// Post: Return nullptr if succesful
AVLNode* FoodItemAVL::deleteNodeRecursive(AVLNode* aNode, const string& itemName)
{
    // Check if the current node is null
    if (aNode == nullptr)
        return aNode; // Return nullptr since the item was not found
    // Compare the item name with the current node's food item's name
    if (itemName < aNode->foodItem.getName())
        // If the desired item name is smaller, recursively search in the left subtree
        aNode->left = deleteNodeRecursive(aNode->left, itemName);
    
    else if (itemName > aNode->foodItem.getName())
        // If the desired item name is greater, recursively search in the right subtree
        aNode->right = deleteNodeRecursive(aNode->right, itemName);
    else
    {
        // Case: Found the node with the desired item name
        if (aNode->left == nullptr || aNode->right == nullptr)
        {
            // Create a temporary pointer to the non-null child (if any)
            AVLNode* temp = (aNode->left != nullptr) ? aNode->left : aNode->right;

            if (temp == nullptr)
            {
                // If both children are null, remove the current node
                temp = aNode;
                aNode = nullptr;
            }
            else
                *aNode = *temp; // Copy the contents of the non-null child to current node
            delete temp; // Delete the temporary node
        }
        else
        {
            // Case: Node has two children
            // If the current node has both left and right children
            AVLNode* temp = aNode->right; 
            // Find the minimum value node in the right subtree
            while (temp->left != nullptr)
                temp = temp->left;
            // Copy the data of the leftmost node to the current node
            aNode->foodItem = temp->foodItem;
            // Recursively delete the leftmost node from the right subtree
            aNode->right = deleteNodeRecursive(aNode->right, temp->foodItem.getName());
        }
    }
    // Update the height of the current node after deletion
    if (aNode == nullptr)
        return aNode; // If the node was deleted, return nullptr
    aNode->height = 1 + max(getHeight(aNode->left), getHeight(aNode->right));
    // Rebalance the tree if necessary and return the updated node
    return balanceNode(aNode);
}

// recurisive print function 
void FoodItemAVL::printInOrderRecursive(AVLNode* aNode)
{
    // Base case: If the current node is null, return
    if (aNode == nullptr)
        return;

	// Recursively print the left subtree
    printInOrderRecursive(aNode->left);
    
	// Print the current node's food item's name
    if (aNode->foodItem.getAvailability() == true)
    {
        cout << aNode->foodItem.getName()
            << "\t$" << aNode->foodItem.getPrice() << endl;
    }


	// Recursively print the right subtree
    printInOrderRecursive(aNode->right);
}

// recursive print function (all items)
void FoodItemAVL::printAllInOrderRecursive(AVLNode* aNode)
{
    // Base case: If the current node is null, return
    if (aNode == nullptr)
        return;

    // Recursively print the left subtree
    printAllInOrderRecursive(aNode->left);

    // Print the current node's food item's details
    cout << aNode->foodItem.getName()
        << "\t$" << aNode->foodItem.getPrice()
        << "\tAvailable: " << (aNode->foodItem.getAvailability() ? "True" : "False")
        << endl;

    // Recursively print the right subtree
    printAllInOrderRecursive(aNode->right);
}


// Insert node into the AVL tree
// Pre : Tree must exist i guess
// Post: The node will be inserted into the tree int the correct position
//       It will automatically correct the structure of the tree if unbalanced
void FoodItemAVL::insertNode(FoodItem aFoodItem)
{
	// call recursive insert function
    root = insertNodeRecursive(root, aFoodItem);
}

// Search for an item by the food item Name
// Pre : Not a null AVL Tree
// Post: Returns the address of the foodItem stored within the tree
FoodItem* FoodItemAVL::searchNode(string& foodItemName)
{
    // Call the recursive searchNodeRecursive function to find the node with the desired item name
    AVLNode* foundNode = searchNodeRecursive(root, foodItemName);
    
    // Check if the desired item node was found
    if (foundNode != nullptr)
        // Return a pointer to the food item within the found node
        return &(foundNode->foodItem);
    // Return nullptr if the item was not found
    return nullptr;
}

// Print in alphabetical order (A-Z)
// Pre : Not a null AVL Tree
// Post: Prints the full item menu of the restaurant in which the AVL tree belongs to
void FoodItemAVL::printInOrder()
{
	// Call the recursive printInOrderRecursive function to print the tree in alphabetical order
    printInOrderRecursive(root);
}

// Print in alphabetical order (A-Z) (all items)
// Pre : Not a null AVL Tree
// Post: Prints the full item menu of the restaurant in which the AVL tree belongs to
void FoodItemAVL::printAllInOrder()
{
	// Call the recursive printInOrderRecursive function to print the tree in alphabetical order
	printAllInOrderRecursive(root);
}

// Delete a node inside AVL Tree by searching for its name
// Pre : Not a null AVL Tree 
// Post: Returns true if the Node has been successfully delted & tree auto balances
//       Returns false if unable to find node
bool FoodItemAVL::deleteNode(string& itemName)
{
    // Call the recursive deleteNodeRecursive function to delete the node with the desired item name
    AVLNode* newRoot = deleteNodeRecursive(root, itemName);

    // Update the root of the AVL tree
    if (newRoot != nullptr) {
        root = newRoot;
        return true; // Successfully deleted the node
    }
    return false; // Node with itemName not found or tree is now empty
}


// Function to delete the entire AVL Tree
void FoodItemAVL::deleteTree(AVLNode* aNode) {
    
	// Base case: If the current node is null, return
    if (aNode != nullptr) {
		// Recursively delete the left and right subtrees
        deleteTree(aNode->left);
        deleteTree(aNode->right);
        delete aNode; // Delete the current node
    }
}
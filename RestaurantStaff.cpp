#include "RestaurantStaff.h"

// Constructor
RestaurantStaff::RestaurantStaff()
{
}

// Parameterized Constructor
// 1 : 1 relationship between Staff and Restaurant Branch
RestaurantStaff::RestaurantStaff(string aBranchName)
{
	branchName = aBranchName;
}


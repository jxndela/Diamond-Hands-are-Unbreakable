/*
 * T03 Jonathan Ho S10246045 Ong Jun Jie S10240117
 * Done by Jonathan Ho
 */
#include "User.h"

// Constructor
User::User()
{
	email = "guest@np.com";
	passwordHash = "";
}

User::User(string aEmailKey, string hashedPassword)
{
	email = aEmailKey;
	passwordHash = hashedPassword;
}

User::~User(){}



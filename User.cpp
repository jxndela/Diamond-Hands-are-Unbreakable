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



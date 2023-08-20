#pragma once
#include <iostream>
#include <string>

using namespace std;

class User
{
protected:

    string email;           // Store user email
    string passwordHash;    // Store user password hash

public:

    // Constructors
    User();

    // Parameterized Constructor
    User(string aEmailKey, string hashedPassword);

    // Destructors
    ~User();
};


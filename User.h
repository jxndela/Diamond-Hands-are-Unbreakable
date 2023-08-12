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

    // Check the passwordHash of a user object
    // Pre : ~
    // Post: Returns passwordHash
    string getPasswordHash();

    // Check the email of a user object
    // Pre : ~
    // Post: Returns email
    string getEmail();
};


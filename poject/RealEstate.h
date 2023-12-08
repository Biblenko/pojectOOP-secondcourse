#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include "Adress.h"
#include "User.h"
#include "Property.h"

class RealEstate {
    User currentUser;
    std::vector<User> users;
    std::vector<Property> properties;
    std::vector<Address> addresses;
public:

    User createUser();
    User& loginUser();
    void userMenu();

    Property createProperty(Address, int, double, std::string, bool, int, int, User);
    std::vector<Property> searchProperties();
    bool postNewProperty(User&);
    void removeProperty(User&);
    void printAllProperties();
    void printUserProperties(User&);
        
    Address createAddress(std::string, std::string);

    bool isUsernameTaken(std::string);

    bool isPasswordStrong(std::string);
};

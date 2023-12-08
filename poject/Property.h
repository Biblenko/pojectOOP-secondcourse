#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Adress.h"
#include "User.h"

class Property {
    Address address;
    int rooms;
    double price;
    std::string property_type;
    bool is_for_rent;
    int house_number;
    int floor_number;
    User owner;
public:
    Property(Address address, int rooms, double price, std::string property_type, bool is_for_rent, int house_number, int floor_number, User owner)
        : address(address), rooms(rooms), price(price), property_type(property_type), is_for_rent(is_for_rent), house_number(house_number), floor_number(floor_number), owner(owner) {}

    User& getOwner() { return owner; };
    Address& getAdress() { return address; };

    bool isRent() { return is_for_rent; };
    int getRoomsCount() { return rooms; };
    int getPrice() { return price; };
    int getHouseNumber() { return house_number; };
    int getFloorNumber() { return floor_number; };
    std::string getPropertyType() { return property_type; };

    std::string toString() const {
        std::string typeDescription;
        if (property_type == "Standard Apartment") {
            typeDescription = "Standard apartment";
        }
        else if (property_type == "Penthouse") {
            typeDescription = "Penthouse";
        }
        else if (property_type == "Private House") {
            typeDescription = "Private house";
        }

        std::string rentOrSale = is_for_rent ? "For rent" : "For sale";
        std::string floorInfo = (property_type == "Standard Apartment" || property_type == "Penthouse") ? (", Floor " + std::to_string(floor_number)) : "";

        return typeDescription + ": " + std::to_string(rooms) + " rooms" + floorInfo + ".\n"
            + "Price: " + std::to_string(price) + " dollars.\n"
            + "Contact information: " + owner.toString();
    }
};


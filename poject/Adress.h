#pragma once

#include <iostream>

class Address {
    std::string city;
    std::string street;
public:
    Address(std::string city, std::string street) : city(city), street(street) {}

    std::string getCity() { return city; };
    std::string getStreet() { return street; };
};
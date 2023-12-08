#pragma once

#include <iostream>

class User {
    std::string username;
    std::string password;
    std::string phone_number;
    bool is_broker;
    int posted_properties_count;
public:
    User(std::string username, std::string password, std::string phone_number, bool is_broker = false)
        : username(username), password(password), phone_number(phone_number), is_broker(is_broker), posted_properties_count(0) {}

    User()
        : username(""), password(""), phone_number(""), is_broker(false), posted_properties_count(0) {};

    std::string toString() const {
        return "Username: " + username + ", Phone: " + phone_number + ", Broker: " + (is_broker ? "Yes" : "No");
    }

    std::string getUsername() { return username; };
    std::string getPassword() { return password; };
    bool getIsBroker() { return is_broker; };
    int getPostedProperties() { return posted_properties_count; };

    void operator ++(int) { posted_properties_count++; };
    void operator --(int) { posted_properties_count--; };
};


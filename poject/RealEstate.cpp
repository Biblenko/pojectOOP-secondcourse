#include "RealEstate.h"

User RealEstate::createUser() {
    std::string username, password, phone_number;
    bool is_broker;

    // �������� ������������ ����� ������������
    do {
        std::cout << "������� ��� ������������: ";
        std::cin >> username;

        if (isUsernameTaken(username)) {
            std::cout << "��� ������������ ��� ������. ����������, �������� ������." << std::endl;
        }
    } while (isUsernameTaken(username));

    // �������� ���������� ������
    do {
        std::cout << "������� ������ (������ ��������� ���� �� ���� ����� � ���� �� �������� $,% ��� _): ";
        std::cin >> password;

        if (!isPasswordStrong(password)) {
            std::cout << "������ �� �������� ��������. ����������, �������� ��������� �����������." << std::endl;
        }
    } while (!isPasswordStrong(password));

    std::cout << "������� ����� ��������: ";
    std::cin >> phone_number;
    std::cout << "�� ������? (1 - ��, 0 - ���): ";
    std::cin >> is_broker;

    User user(username, password, phone_number, is_broker);
    users.push_back(user);

    std::cout << "������� ������ ������� ��� ������������ " << user.getUsername() << std::endl;

    return user;
}

User& RealEstate::loginUser() {
    std::string username, password;

    std::cout << "������� ��� ������������: ";
    std::cin >> username;
    std::cout << "������� ������: ";
    std::cin >> password;

    for (User& user : users) {
        if (user.getUsername() == username && user.getPassword() == password) {
            currentUser = user;
            return user;
        }
    }

    std::cout << "�������� ��� ������������ ��� ������. ������� � ������� ����." << std::endl;
    return currentUser;
}

void RealEstate::userMenu() {
    while (true) {
        std::cout << "User Menu:" << std::endl;
        std::cout << "1 - Post new property" << std::endl;
        std::cout << "2 - Remove property publication" << std::endl;
        std::cout << "3 - View all properties" << std::endl;
        std::cout << "4 - View user's properties" << std::endl;
        std::cout << "5 - Search properties by parameters" << std::endl;
        std::cout << "6 - Log out and return to the main menu" << std::endl;

        int choice;
        std::cout << "Choose an action: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            postNewProperty(currentUser);
            break;
        case 2:
            removeProperty(currentUser);
            break;
        case 3:
            printAllProperties();
            break;
        case 4:
            printUserProperties(currentUser);
            break;
        case 5:
        {
            std::vector<Property> searchResult = searchProperties();
            if (!searchResult.empty()) {
                std::cout << "Search results:" << std::endl;
                for (const auto& property : searchResult) {
                    std::cout << property.toString() << std::endl;
                }
            }
            else {
                std::cout << "No properties found matching the criteria." << std::endl;
            }
        }
        break;
        case 6:
            return;  // ����� �� ������ ������������
        default:
            std::cout << "Invalid input. Please choose a number between 1 and 6." << std::endl;
        }
    }
}

Property RealEstate::createProperty(Address address, int rooms, double price, std::string property_type, bool is_for_rent, int house_number, int floor_number, User owner) {
    Property property(address, rooms, price, property_type, is_for_rent, house_number, floor_number, owner);
    properties.push_back(property);
    return property;
}

std::vector<Property> RealEstate::searchProperties() {
    std::vector<Property> result;

    bool is_for_rent;
    std::string property_type;
    int rooms;
    double min_price;
    double max_price;

    std::cout << "Is the property for rent? (1 - Yes, 0 - No, 999 - No preference): ";
    std::cin >> is_for_rent;

    std::cout << "What type of property do you want? (1 - Standard Apartment, 2 - Penthouse, 3 - Private House, 999 - No preference): ";
    std::cin >> property_type;

    std::cout << "How many rooms do you want? (999 - No preference): ";
    std::cin >> rooms;

    std::cout << "Enter the minimum price (999 for no preference): ";
    std::cin >> min_price;

    std::cout << "Enter the maximum price (999 for no preference): ";
    std::cin >> max_price;

    for (Property& property : properties) {
        if ((is_for_rent == 999 || property.isRent() == static_cast<bool>(is_for_rent))
            && (property_type == "999" || property.getPropertyType() == property_type)
            && (rooms == 999 || property.getRoomsCount() == rooms)
            && (min_price == 999 || property.getPrice() >= min_price)
            && (max_price == 999 || property.getPrice() <= max_price)) {
            result.push_back(property);
        }
    }

    return result;
}

bool RealEstate::postNewProperty(User& user) {
    // �������� �� ����� ���������� �������
    int max_properties_limit = user.getIsBroker() ? 10 : 3;
    if (user.getPostedProperties() >= max_properties_limit) {
        std::cout << "��������� ����� ����������� �������. ������ ���������� ������." << std::endl;
        return false;
    }

    // ����� ������ �������
    std::cout << "������ ������� � �������:" << std::endl;
    for (Address& address : addresses) {
        std::cout << address.getCity() << std::endl;
    }

    // ���� ������
    std::string selectedCity;
    std::cout << "������� �������� ������: ";
    std::cin >> selectedCity;

    // �������� ����� ������
    auto cityIterator = std::find_if(addresses.begin(), addresses.end(),
        [&selectedCity](Address& addr) { return addr.getCity() == selectedCity; });

    if (cityIterator == addresses.end()) {
        std::cout << "�������� �������� ������. ������� � ������� ����." << std::endl;
        return false;
    }

    // ����� ������ ���� ��� ���������� ������
    std::cout << "������ ���� � ������ " << selectedCity << ":" << std::endl;
    for (Address& address : addresses) {
        if (address.getCity() == selectedCity) {
            std::cout << address.getStreet() << std::endl;
        }
    }

    // ���� �����
    std::string selectedStreet;
    std::cout << "������� �������� �����: ";
    std::cin >> selectedStreet;

    // �������� ����� �����
    auto streetIterator = std::find_if(addresses.begin(), addresses.end(),
        [&selectedCity, &selectedStreet](Address& addr) { return addr.getCity() == selectedCity && addr.getStreet() == selectedStreet; });

    if (streetIterator == addresses.end()) {
        std::cout << "�������� �������� �����. ������� � ������� ����." << std::endl;
        return false;
    }

    // ... ������ ����� ��������� ������ � �������� ������� Property ...

    // ���������� �������� ����������� ������� ������������
    user++;

    std::cout << "������������ ������� ���������." << std::endl;

    return true;
}

void RealEstate::removeProperty(User& user) {
    if (user.getPostedProperties() == 0) {
        std::cout << "�� ��� �� ������������ �� ������ ��������." << std::endl;
        return;
    }

    std::cout << "���� �������������� ��������:" << std::endl;
    int propertyNumber = 1;
    for (Property& property : properties) {
        if (property.getOwner().getUsername() == user.getUsername()) {
            std::cout << propertyNumber << ". " << property.getAdress().getCity() << ", " << property.getAdress().getStreet() << std::endl;
            propertyNumber++;
        }
    }

    int selectedPropertyNumber;
    std::cout << "�������� ����� �������� ��� ��������: ";
    std::cin >> selectedPropertyNumber;

    propertyNumber = 1;
    for (auto it = properties.begin(); it != properties.end(); ++it) {
        if (it->getOwner().getUsername() == user.getUsername()) {
            if (propertyNumber == selectedPropertyNumber) {
                properties.erase(it);
                std::cout << "���������� �������� ������� �������." << std::endl;
                user--;
                return;
            }
            propertyNumber++;
        }
    }

    std::cout << "�������� ����� ��������. ������� � ������� ����." << std::endl;
}

void RealEstate::printAllProperties() {
    std::cout << "��� ������ � �������:" << std::endl;
    for (Property& property : properties) {
        std::cout << property.getAdress().getCity() << ", " << property.getAdress().getStreet() << std::endl;
    }
}

void RealEstate::printUserProperties(User& user) {
    std::cout << "���� �������������� ��������:" << std::endl;
    for (Property& property : properties) {
        if (property.getOwner().getUsername() == user.getUsername()) {
            std::cout << property.getAdress().getCity() << ", " << property.getAdress().getStreet() << std::endl;
        }
    }
}

Address RealEstate::createAddress(std::string city, std::string street) {
    Address address(city, street);
    addresses.push_back(address);
    return address;
}

bool RealEstate::isUsernameTaken(std::string username) {
    for (User& user : users) {
        if (user.getUsername() == username) {
            return true; // ��� ������������ ��� ������
        }
    }
    return false;
}

bool RealEstate::isPasswordStrong(std::string password) {
    bool has_digit = false;
    bool has_special_char = false;
    //bool is_long_8 = password.length() > 8;

    for (char ch : password) {
        if (isdigit(ch)) {
            has_digit = true;
        }
        else if (ch == '$' || ch == '%' || ch == '_') {
            has_special_char = true;
        }
    }

    return has_digit && has_special_char /*&& is_long_8*/;
}
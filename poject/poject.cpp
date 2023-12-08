#include "RealEstate.h"

int main() {
    setlocale(0, "rus");
    RealEstate realEstateSystem;

    while (true) {
        std::cout << "Главное меню:" << std::endl;
        std::cout << "1 - Создать учетную запись" << std::endl;
        std::cout << "2 - Войти в существующую учетную запись" << std::endl;
        std::cout << "3 - Завершить программу" << std::endl;

        int choice;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        if (choice == 1) {
            realEstateSystem.createUser();
        }
        else if (choice == 2) {
            User user = realEstateSystem.loginUser();
            if (user.getUsername() != "") {
                realEstateSystem.userMenu();
            }
        }
        else if (choice == 3) {
            std::cout << "Программа завершена." << std::endl;
            break;
        }
        else {
            std::cout << "Неверный ввод. Пожалуйста, выберите 1, 2 или 3." << std::endl;
        }
    }

    return 0;
}

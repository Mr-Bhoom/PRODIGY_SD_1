#include "contact_manager.h"

void showMenu() {
    std::cout << "Contact Manager" << std::endl;
    std::cout << "1. Add new contact" << std::endl;
    std::cout << "2. View contacts" << std::endl;
    std::cout << "3. Edit contact" << std::endl;
    std::cout << "4. Delete contact" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

int main() {
    ContactManager manager;
    int choice;

    while (true) {
        showMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 5) {
            std::cout << "Exiting program." << std::endl;
            break;
        }

        std::string name, phone, email;
        int index;
        switch (choice) {
            case 1:
                std::cout << "Enter name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter phone: ";
                std::getline(std::cin, phone);
                std::cout << "Enter email: ";
                std::getline(std::cin, email);
                manager.addContact(Contact(name, phone, email));
                break;
            case 2:
                manager.viewContacts();
                break;
            case 3:
                std::cout << "Enter contact index to edit: ";
                std::cin >> index;
                std::cin.ignore();
                std::cout << "Enter new name: ";
                std::getline(std::cin, name);
                std::cout << "Enter new phone: ";
                std::getline(std::cin, phone);
                std::cout << "Enter new email: ";
                std::getline(std::cin, email);
                manager.editContact(index, Contact(name, phone, email));
                break;
            case 4:
                std::cout << "Enter contact index to delete: ";
                std::cin >> index;
                manager.deleteContact(index);
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}

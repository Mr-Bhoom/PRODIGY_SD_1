#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

#include "contact.h"
#include <vector>
#include <iostream>
#include <fstream>

class ContactManager {
private:
    std::vector<Contact> contacts;

    void loadContactsFromFile() {
        std::ifstream file("contacts.txt");
        if (!file) return;

        std::string name, phone, email;
        while (std::getline(file, name) && std::getline(file, phone) && std::getline(file, email)) {
            contacts.emplace_back(name, phone, email);
        }
        file.close();
    }

    void saveContactsToFile() {
        std::ofstream file("contacts.txt");
        for (const auto &contact : contacts) {
            file << contact.getName() << "\n" << contact.getPhone() << "\n" << contact.getEmail() << "\n";
        }
        file.close();
    }

public:
    ContactManager() {
        loadContactsFromFile();
    }

    ~ContactManager() {
        saveContactsToFile();
    }

    void addContact(const Contact &contact) {
        contacts.push_back(contact);
    }

    void viewContacts() const {
        for (const auto &contact : contacts) {
            contact.print();
            std::cout << "------------------" << std::endl;
        }
    }

    void editContact(int index, const Contact &newContact) {
        if (index >= 0 && index < contacts.size()) {
            contacts[index] = newContact;
        } else {
            std::cout << "Invalid contact index." << std::endl;
        }
    }

    void deleteContact(int index) {
        if (index >= 0 && index < contacts.size()) {
            contacts.erase(contacts.begin() + index);
        } else {
            std::cout << "Invalid contact index." << std::endl;
        }
    }

    int getContactCount() const {
        return contacts.size();
    }
};

#endif // CONTACT_MANAGER_H

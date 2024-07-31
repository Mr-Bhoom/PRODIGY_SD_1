#ifndef CONTACT_H
#define CONTACT_H

#include <string>

class Contact {
private:
    std::string name;
    std::string phone;
    std::string email;

public:
    Contact() = default;
    Contact(const std::string &name, const std::string &phone, const std::string &email)
        : name(name), phone(phone), email(email) {}

    // Getters
    std::string getName() const { return name; }
    std::string getPhone() const { return phone; }
    std::string getEmail() const { return email; }

    // Setters
    void setName(const std::string &newName) { name = newName; }
    void setPhone(const std::string &newPhone) { phone = newPhone; }
    void setEmail(const std::string &newEmail) { email = newEmail; }

    // Print contact information
    void print() const {
        std::cout << "Name: " << name << "\nPhone: " << phone << "\nEmail: " << email << std::endl;
    }
};

#endif // CONTACT_H

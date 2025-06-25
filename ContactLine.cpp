#include "ContactLine.h"
#include <iostream>

namespace NLine {
    ContactLine::ContactLine(std::string name, std::string surname, std::string email)
        : name(name), surname(surname), email(email) {}

    void ContactLine::print() const {
        std::cout << "Contact: " << name << " " << surname << ", e-mail: " << email << std::endl;
    }
    
    std::string ContactLine::serialize() const {
        return "CONTACT:" + name + ":" + surname + ":" + email;
    }
    
    ContactLine* ContactLine::deserialize(const std::string& data) {
        size_t pos1 = data.find(":", 8);
        size_t pos2 = data.find(":", pos1 + 1);
        std::string name = data.substr(8, pos1 - 8);
        std::string surname = data.substr(pos1 + 1, pos2 - (pos1 + 1));
        std::string email = data.substr(pos2 + 1);
        return new ContactLine(name, surname, email);
    }
}
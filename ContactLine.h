#ifndef CONTACTLINE_H
#define CONTACTLINE_H

#include "Line.h"
#include <string>

namespace NLine {
    class ContactLine : public Line_ {
        std::string name;
        std::string surname;
        std::string email;
    public:
        ContactLine(std::string name, std::string surname, std::string email);
        void print() const override;
        std::string serialize() const override;
        static ContactLine* deserialize(const std::string& data);
    };
}
#endif //CONTACTLINE_H
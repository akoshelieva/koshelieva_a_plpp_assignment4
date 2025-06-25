#include "CheckList.h"
#include <iostream>

namespace NLine {
    Checklist::Checklist(const std::string& i, bool c) : item(i), checked(c) {}

    void Checklist::print() const {
        std::cout << "[ " << (checked ? "+" : "-") << " ] " << item << std::endl;
    }

    std::string Checklist::serialize() const {
        return "CHECK:" + std::string(checked ? "+" : "-") + ':' + item;
    }

    Checklist* Checklist::deserialize(const std::string& data) {
        bool check = (data[6] == '+');
        std::string item = data.substr(8);
        return new Checklist(item, check);
    }
}
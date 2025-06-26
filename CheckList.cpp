#include "CheckList.h"
#include <iostream>

namespace NLine {
    ChecklistLine::ChecklistLine(const std::string& i, bool c) : item(i), checked(c) {}

    void ChecklistLine::print() const {
        std::cout << "[ " << (checked ? "+" : "-") << " ] " << item << std::endl;
    }

    std::string ChecklistLine::serialize() const {
        return "CHECK:" + std::string(checked ? "+" : "-") + ':' + item;
    }

    ChecklistLine* ChecklistLine::deserialize(const std::string& data) {
        bool check = (data[6] == '+');
        std::string item = data.substr(8);
        return new ChecklistLine(item, check);
    }
}
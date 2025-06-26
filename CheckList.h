#ifndef CHECKLIST_H
#define CHECKLIST_H

#include "Line.h"
#include <string>

namespace NLine {
    class ChecklistLine : public Line_ {
        std::string item;
        bool checked;
    public:
        ChecklistLine(const std::string& i, bool c);
        void print() const override;
        std::string serialize() const override;
        static ChecklistLine* deserialize(const std::string& data);
    };
}
#endif //CHECKLIST_H//

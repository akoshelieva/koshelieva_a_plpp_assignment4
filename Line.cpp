#include "Line.h"
#include <iostream>
#include "Line.h"
#include "TextLine.h"
#include "CheckList.h"
#include "ContactLine.h"
#include <stdexcept>
NLine::Line_* NLine::Line_::deserialize(const std::string& data) {
    if (data.rfind("TEXT:", 0) == 0) {
        return NLine::TextLine::deserialize(data);
    }
    if (data.rfind("CHECK:", 0) == 0) {
        return NLine::ChecklistLine::deserialize(data);
    }
    if (data.rfind("CONTACT:", 0) == 0) {
        return NLine::ContactLine::deserialize(data);
    }
    throw std::invalid_argument("Unknown line format for deserialization.");
}
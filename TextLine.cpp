#include "TextLine.h"
#include <iostream>

namespace NLine {
    TextLine::TextLine(const std::string& t) : text(t) {}

    void TextLine::print() const {
        std::cout << "Text: " << text << std::endl;
    }
    std::string TextLine::serialize() const {
        return "TEXT:" + text;
    }
    TextLine* TextLine::deserialize(const std::string& data) {
        return new TextLine(data.substr(5));
    }
}
#ifndef TEXTLINE_H
#define TEXTLINE_H

#include "Line.h"
#include <string>

namespace NLine {
    class TextLine : public Line_ {
        std::string text;
    public:
        TextLine(const std::string& t);
        void print() const override;
        std::string serialize() const override;
        static TextLine* deserialize(const std::string& data);
    };
}
#endif //TEXTLINE_H
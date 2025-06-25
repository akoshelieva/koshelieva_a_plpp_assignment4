#ifndef LINE_H
#define LINE_H

#include <string>
namespace NLine {
    class Line_ {
    public:
        virtual void print() const = 0;
        virtual std::string serialize() const = 0;
        virtual ~Line_() = default;
        static Line_* deserialize(const std::string& data);
    };
}
#endif //LINE_H
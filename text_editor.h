#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>

namespace NLine {
    class Line_;
}

class Line_ {
public:
    virtual void print() const = 0;
    virtual std::string serialize() const = 0;
    virtual ~Line_() {}
    static Line_* deserialize(const std::string& data);
};

class TextLine : public Line_ {
    std::string text;
public:
    TextLine(const std::string& t) : text(t) {}
    void print() const override;
    std::string serialize() const override;
    static TextLine* deserialize(const std::string& data);
};

class ChecklistLine : public Line_ {
    std::string item;
    bool checked;
public:
    ChecklistLine(const std::string& i, bool c) : item(i), checked(c) {}
    void print() const override;
    std::string serialize() const override;
    static ChecklistLine* deserialize(const std::string& data);
};

class ContactLine : public Line_ {
    std::string name, surname, email;
public:
    ContactLine(const std::string& n, const std::string& s, const std::string& e)
        : name(n), surname(s), email(e) {}
    void print() const override;
    std::string serialize() const override;
    static ContactLine* deserialize(const std::string& data);
};

class CaesarCipher;

class TextEditor {
private:
    std::vector<NLine::Line_*> lines;
    std::vector<std::string> changes;
    std::string clipboard;
    size_t changes_index;
    static const size_t MAX_CHANGES = 5;

    void saveState();
    std::string serializeAll() const;
    void deserializeAll(const std::string& data);

public:
    TextEditor();
    ~TextEditor();

    void addTextLine(const std::string& text);
    void addChecklistLine(const std::string& item, bool checked);
    void addContactLine(const std::string& name, const std::string& surname, const std::string& email);
    void insertLine(size_t index, const std::string &serializedLine);
    void deleteLine(size_t index);
    void replaceLine(size_t index, const std::string &serializedLine);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void copyLine(size_t index);
    void pasteLine(size_t index);
    void undo();
    void redo();
    void printAll() const;
    void searchText(const std::string& text_to_find) const;
    void saveEncrypted(const std::string& filename, int key);
    void loadEncrypted(const std::string& filename, int key);

};

#endif // TEXTEDITOR_H#ifndef TEXTEDITOR_H

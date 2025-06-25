#include "text_editor.h"
#include "TextLine.h"
#include "CheckList.h"
#include "ContactLine.h"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ceasar.h"

TextEditor::TextEditor() : changes_index(0) {
    changes.push_back("");
}

TextEditor::~TextEditor() {
    for (auto line : lines) {
        delete line;
    }
}

void TextEditor::saveState() {
    if (changes_index < changes.size() - 1) {
        changes.erase(changes.begin() + changes_index + 1, changes.end());
    }
    changes.push_back(serializeAll());
    changes_index = changes.size() - 1;
    if (changes.size() > MAX_changes) {
        changes.erase(changes.begin());
        changes_index--;
    }
}

std::string TextEditor::serializeAll() const {
    std::stringstream ss;
    for (const auto& line : lines) {
        ss << line->serialize() << "\n";
    }
    return ss.str();
}

void TextEditor::deserializeAll(const std::string& data) {
    for (auto line : lines) {
        delete line;
    }
    lines.clear();
    std::stringstream ss(data);
    std::string lineData;
    while (std::getline(ss, lineData)) {
        if (!lineData.empty()) {
            lines.push_back(NLine::Line_::deserialize(lineData));
        }
    }
}

void TextEditor::addTextLine(const std::string& text) {
    saveState();
    lines.push_back(new NLine::TextLine(text));
}

void TextEditor::addChecklistLine(const std::string& item, bool checked) {
    saveState();
    lines.push_back(new NLine::Checklist(item, checked));
}

void TextEditor::addContactLine(const std::string& name, const std::string& surname, const std::string& email) {
    saveState();
    lines.push_back(new NLine::ContactLine(name, surname, email));
}

void TextEditor::insertLine(size_t index, const std::string& serializedLine) {
    if (index > lines.size()) {
        throw std::out_of_range("Invalid line index");
    }
    saveState();
    lines.insert(lines.begin() + index, NLine::Line_::deserialize(serializedLine));
}

void TextEditor::deleteLine(size_t index) {
    if (index >= lines.size()) {
        throw std::out_of_range("Invalid line index");
    }
    saveState();
    delete lines[index];
    lines.erase(lines.begin() + index);
}

void TextEditor::replaceLine(size_t index, const std::string& serializedLine) {
    if (index >= lines.size()) {
        throw std::out_of_range("Invalid line index");
    }
    saveState();
    delete lines[index];
    lines[index] = NLine::Line_::deserialize(serializedLine);
}

void TextEditor::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << serializeAll();
        file.close();
        std::cout << "Text saved to " << filename << std::endl;
    } else {
        std::cerr << "Error: Could not open file for saving: " << filename << std::endl;
    }
}

void TextEditor::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string loaded_text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        saveState();
        deserializeAll(loaded_text);
        std::cout << "Text loaded from " << filename << std::endl;
    } else {
        std::cerr << "Error: Could not open file for loading: " << filename << std::endl;
    }
}

void TextEditor::copyLine(size_t index) {
    if (index >= lines.size()) {
        throw std::out_of_range("Invalid line index");
    }
    clipboard = lines[index]->serialize();
}

void TextEditor::pasteLine(size_t index) {
    if (clipboard.empty()) {
        std::cout << "Clipboard is empty, nothing to paste.\n";
        return;
    }
    if (index > lines.size()) {
        throw std::out_of_range("Invalid line index");
    }
    saveState();
    lines.insert(lines.begin() + index, NLine::Line_::deserialize(clipboard));
}

void TextEditor::undo() {
    if (changes_index > 0) {
        changes_index--;
        deserializeAll(changes[changes_index]);
        std::cout << "Undo successful.\n";
    } else {
        std::cout << "Cannot undo: Already at oldest state.\n";
    }
}

void TextEditor::redo() {
    if (changes_index < changes.size() - 1) {
        changes_index++;
        deserializeAll(changes[changes_index]);
        std::cout << "Redo successful.\n";
    } else {
        std::cout << "Cannot redo: Already at latest state.\n";
    }
}

void TextEditor::printAll() const {
    if (lines.empty()) {
        std::cout << "Text is empty.\n";
        return;
    }
    for (const auto& line : lines) {
        line->print();
    }
}

void TextEditor::searchText(const std::string& text_to_find) const {
    if (text_to_find.empty()) {
        std::cout << "Search string is empty.\n";
        return;
    }
    bool found = false;
    for (size_t i = 0; i < lines.size(); ++i) {
        std::string serialized = lines[i]->serialize();
        size_t pos = serialized.find(text_to_find);
        if (pos != std::string::npos) {
            std::cout << "Found \"" << text_to_find << "\" in line " << i << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "Text \"" << text_to_find << "\" not found.\n";
    }
}

void TextEditor::loadEncrypted(const std::string& filename, int key) {
    CaesarCipher cipher("caesar.dll");

    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Could not open file for loading: " + filename);
    }

    std::string encrypted_data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();

    size_t len = encrypted_data.length();
    if (len == 0) return;

    uint8_t* encrypted_bytes = reinterpret_cast<uint8_t*>(const_cast<char*>(encrypted_data.c_str()));

    uint8_t* decrypted = cipher.decrypt(encrypted_bytes, len - 1, key);
    if (!decrypted) {
        throw std::runtime_error("Decryption failed");
    }

    std::string decryptedStr(reinterpret_cast<char*>(decrypted));
    delete[] decrypted;

    saveState();
    deserializeAll(decryptedStr);
    std::cout << "Encrypted text loaded from " << filename << std::endl;
}

void TextEditor::saveEncrypted(const std::string& filename, int key) {
    CaesarCipher cipher("caesar.dll");
    std::string serialized = serializeAll();
    size_t len = serialized.length();
    if (len == 0) return;
    uint8_t* encrypted = cipher.encrypt(reinterpret_cast<const uint8_t*>(serialized.c_str()), len, key);
    if (!encrypted) {
        throw std::runtime_error("Encryption failed");
    }
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        delete[] encrypted;
        throw std::runtime_error("Could not open file for saving: " + filename);
    }
    out.write(reinterpret_cast<char*>(encrypted), len);
    delete[] encrypted;
    std::cout << "Encrypted text saved to " << filename << std::endl;
}
#include "text_editor.h"
#include <iostream>
#include <limits>
#include <string>

void clear_input_buffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    TextEditor editor;
    int choice;

    while (true) {
        std::cout << "\n=== Text Editor Menu ===\n"
                  << "1. Add Text Line\n"
                  << "2. Add Checklist Line\n"
                  << "3. Add Contact Line\n"
                  << "4. Insert Line\n"
                  << "5. Delete Line\n"
                  << "6. Copy Line\n"
                  << "7. Paste Line\n"
                  << "8. Replace Line\n"
                  << "9. Search Text\n"
                  << "10. Save to File\n"
                  << "11. Load from File\n"
                  << "12. Save Encrypted\n"
                  << "13. Load Encrypted\n"
                  << "14. Print All\n"
                  << "15. Undo\n"
                  << "16. Redo\n"
                  << "0. Exit\n"
                  << "Enter choice: ";

        if (!(std::cin >> choice)) {
            clear_input_buffer();
            std::cout << "Invalid input.\n";
            continue;
        }
        if (choice == 0) break;

        try {
            size_t index;
            int key;
            std::string text, item, name, surname, email, filename, serializedLine, text_to_find;
            bool checked;

            switch (choice) {
                case 1:
                    std::cout << "Enter text: ";
                    std::cin.ignore();
                    std::getline(std::cin, text);
                    editor.addTextLine(text);
                    break;
                case 2:
                    std::cout << "Enter checklist item: ";
                    std::cin.ignore();
                    std::getline(std::cin, item);
                    std::cout << "Checked (0/1)? ";
                    std::cin >> checked;
                    editor.addChecklistLine(item, checked);
                    break;
                case 3:
                    std::cout << "Enter name, surname, email (each on a new line):\n";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    std::getline(std::cin, surname);
                    std::getline(std::cin, email);
                    editor.addContactLine(name, surname, email);
                    break;
                case 4:
                    std::cout << "Enter index and serialized line (e.g., TEXT:Hello):\n";
                    std::cin >> index;
                    std::cin.ignore();
                    std::getline(std::cin, serializedLine);
                    editor.insertLine(index, serializedLine);
                    break;
                case 5:
                    std::cout << "Enter index to delete: ";
                    std::cin >> index;
                    editor.deleteLine(index);
                    break;
                case 6:
                    std::cout << "Enter index to copy: ";
                    std::cin >> index;
                    editor.copyLine(index);
                    break;
                case 7:
                    std::cout << "Enter index to paste: ";
                    std::cin >> index;
                    editor.pasteLine(index);
                    break;
                case 8:
                    std::cout << "Enter index and serialized line (e.g., TEXT:Hello):\n";
                    std::cin >> index;
                    std::cin.ignore();
                    std::getline(std::cin, serializedLine);
                    editor.replaceLine(index, serializedLine);
                    break;
                case 9:
                    std::cout << "Enter text to search: ";
                    std::cin.ignore();
                    std::getline(std::cin, text_to_find);
                    editor.searchText(text_to_find);
                    break;
                case 10:
                    std::cout << "Enter filename to save: ";
                    std::cin.ignore();
                    std::getline(std::cin, filename);
                    editor.saveToFile(filename);
                    break;
                case 11:
                    std::cout << "Enter filename to load: ";
                    std::cin.ignore();
                    std::getline(std::cin, filename);
                    editor.loadFromFile(filename);
                    break;
                case 12:
                    std::cout << "Enter filename and key:\n";
                    std::cin.ignore();
                    std::getline(std::cin, filename);
                    std::cin >> key;
                    editor.saveEncrypted(filename, key);
                    break;
                case 13:
                    std::cout << "Enter filename and key:\n";
                    std::cin.ignore();
                    std::getline(std::cin, filename);
                    std::cin >> key;
                    editor.loadEncrypted(filename, key);
                    break;
                case 14:
                    editor.printAll();
                    break;
                case 15:
                    editor.undo();
                    break;
                case 16:
                    editor.redo();
                    break;
                default:
                    std::cout << "Invalid choice.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
            clear_input_buffer();
        }
    }

    return 0;
}
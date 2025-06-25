#include <cstdint>
#include <iostream>

extern "C"
{
    __declspec(dllexport) uint8_t* encrypt(uint8_t* rawText, size_t len, int key) {
        if (!rawText || len == 0) {
            return nullptr;
        }
        uint8_t* encryptedText = new uint8_t[len];
        for (size_t i = 0; i < len; i++) {
            encryptedText[i] = (rawText[i] + key) % 256;
        }
        return encryptedText;
    }

    __declspec(dllexport) uint8_t* decrypt(uint8_t* encryptedText, size_t len, int key) {
        if (!encryptedText || len == 0) {
            return nullptr;
        }
        uint8_t* rawText = new uint8_t[len];
        for (size_t i = 0; i < len; i++) {
            rawText[i] = (encryptedText[i] - key + 256) % 256;
        }
        return rawText;
    }
}
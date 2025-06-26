#include <cstdint>
#include <iostream>

extern "C"
{
    __declspec(dllexport) uint8_t* encrypt(const uint8_t* rawText, size_t len, int key) {
        if (!rawText || len == 0) {
            return nullptr;
        }
        uint8_t* encryptedText = new uint8_t[len+1];
        for (size_t i = 0; i < len; i++) {
            encryptedText[i] = (rawText[i] + key) % 256;
        }
        encryptedText[len] = '\0';
        return encryptedText;
    }

    __declspec(dllexport) uint8_t* decrypt(const uint8_t* encryptedText, size_t len, int key) {
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
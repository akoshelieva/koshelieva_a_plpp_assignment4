#include "ceasar.h"
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

CaesarCipher::CaesarCipher(const std::string& dllPath) {
#ifdef _WIN32
    hLib_ = LoadLibraryA(dllPath.c_str());
#else
    hLib_ = dlopen(dllPath.c_str(), RTLD_LAZY);
#endif
    if (!hLib_) {
        throw std::runtime_error("Could not load library: " + dllPath);
    }
#ifdef _WIN32
    encrypt_ = (EncryptFunc)GetProcAddress((HMODULE)hLib_, "encrypt");
    decrypt_ = (DecryptFunc)GetProcAddress((HMODULE)hLib_, "decrypt");
#else
    encrypt_ = (EncryptFunc)dlsym(hLib_, "encrypt");
    decrypt_ = (DecryptFunc)dlsym(hLib_, "decrypt");
#endif
    if (!encrypt_ || !decrypt_) {
        throw std::runtime_error("Could not find functions in library.");
    }
}

CaesarCipher::~CaesarCipher() {
    if (hLib_) {
#ifdef _WIN32
        FreeLibrary((HMODULE)hLib_);
#else
        dlclose(hLib_);
#endif
    }
}

uint8_t* CaesarCipher::encrypt(const uint8_t* text, size_t len, int key) const {
    return encrypt_(const_cast<uint8_t*>(text), len, key);
}

uint8_t* CaesarCipher::decrypt(const uint8_t* encryptedText, size_t len, int key) const {
    return decrypt_(const_cast<uint8_t*>(encryptedText), len, key);
}
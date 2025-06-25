#ifndef CAESAR_CIPHER_H
#define CAESAR_CIPHER_H

#include <string>
#include <cstdint>

class CaesarCipher {
public:
  using EncryptFunc = uint8_t* (*)(uint8_t*, size_t, int);
  using DecryptFunc = uint8_t* (*)(uint8_t*, size_t, int);

  CaesarCipher(const std::string& dllPath);
  ~CaesarCipher();
  uint8_t* encrypt(const uint8_t* text, size_t len, int key) const;
  uint8_t* decrypt(const uint8_t* encryptedText, size_t len, int key) const;

private:
  void* hLib_;
  EncryptFunc encrypt_;
  DecryptFunc decrypt_;
};

#endif
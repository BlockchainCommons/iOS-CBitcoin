//
//  Hash.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/24/18.
//

#ifndef Hash_hpp
#define Hash_hpp

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    void _ripemd160(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength);
    void _sha160(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength);
    void _sha256(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength);
    void _sha256HMAC(const uint8_t* data, size_t dataLength, const uint8_t* key, size_t keyLength, uint8_t** hash, size_t* hashLength);
    void _sha512(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength);
    void _sha512HMAC(const uint8_t* data, size_t dataLength, const uint8_t* key, size_t keyLength, uint8_t** hash, size_t* hashLength);
    void _pkcs5PBKDF2HMACSHA512(const uint8_t* passphrase, size_t passphraseLength, const uint8_t* salt, size_t saltLengh, size_t iterations, uint8_t** hash, size_t* hashLength);
    void _bitcoin256(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength);
    void _bitcoin160(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength);

#ifdef __cplusplus
}
#endif

#endif /* Hash_hpp */

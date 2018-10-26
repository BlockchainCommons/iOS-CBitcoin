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

    void _RIPEMD160Hash(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength);
    void _SHA1Hash(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength);
    void _SHA256Hash(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength);
    void _SHA256HMAC(const uint8_t* data, size_t dataLength, const uint8_t* key, size_t keyLength, uint8_t** hash, size_t* hashLength);
    void _SHA512Hash(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength);
    void _SHA512HMAC(const uint8_t* data, size_t dataLength, const uint8_t* key, size_t keyLength, uint8_t** hash, size_t* hashLength);
    void _PKCS5PBKDf2HMACSHA512(const uint8_t* passphrase, size_t passphraseLength, const uint8_t* salt, size_t saltLengh, size_t iterations, uint8_t** hash, size_t* hashLength);
    void _bitcoinHash(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength);
    void _bitcoinShortHash(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength);

#ifdef __cplusplus
}
#endif

#endif /* Hash_hpp */

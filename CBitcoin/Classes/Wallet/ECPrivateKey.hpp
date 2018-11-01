//
//  ECPrivateKey.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/30/18.
//

#ifndef ECPrivateKey_hpp
#define ECPrivateKey_hpp

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    size_t _ecPrivateKeySize();

    bool _ecNewPrivateKey(const uint8_t* seed, size_t seedLength, uint8_t** privateKey, size_t* privateKeyLength);
    bool _ecPrivateKeyToWIF(const uint8_t* privateKey, size_t privateKeyLength, uint8_t wifVersion, bool isCompressed, char** wif, size_t* wifLength);
    bool _wifToECPrivateKey(const char* wif, uint8_t** privateKey, size_t* privateKeyLength);

#ifdef __cplusplus
}
#endif

#endif /* ECPrivateKey_hpp */

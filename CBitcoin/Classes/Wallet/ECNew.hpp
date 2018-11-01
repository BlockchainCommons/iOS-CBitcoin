//
//  ECNew.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/30/18.
//

#ifndef ECNew_hpp
#define ECNew_hpp

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    size_t _ecPrivateKeySize();
    size_t _ecPublicKeySize();
    size_t _ecUncompressedPublicKeySize();

    bool _ecNew(const uint8_t* seed, size_t seedLength, uint8_t** privateKey, size_t* privateKeyLength);
    bool _ecToPublic(const uint8_t* privateKey, size_t privateKeyLength, uint8_t** publicKey, size_t* publicKeyLength);
    bool _ecToPublicUncompressed(const uint8_t* privateKey, size_t privateKeyLength, uint8_t** publicKey, size_t* publicKeyLength);

#ifdef __cplusplus
}
#endif

#endif /* ECNew_hpp */

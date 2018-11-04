//
//  ECPublicKey.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 11/1/18.
//

#ifndef ECPublicKey_hpp
#define ECPublicKey_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    size_t _ecCompressedPublicKeySize();
    size_t _ecUncompressedPublicKeySize();

    CBitcoinResult _toECPublicKey(const uint8_t* privateKey, size_t privateKeyLength, bool isCompressed, uint8_t** publicKey, size_t* publicKeyLength);
    CBitcoinResult _toECPaymentAddress(const uint8_t* publicKey, size_t publicKeyLength, uint8_t version, char** address, size_t* addressLength);

#ifdef __cplusplus
}
#endif

#endif /* ECPublicKey_hpp */

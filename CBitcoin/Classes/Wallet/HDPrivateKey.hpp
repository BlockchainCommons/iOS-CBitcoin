//
//  HDPrivateKey.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/30/18.
//

#ifndef HDPrivateKey_hpp
#define HDPrivateKey_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    size_t _minimumSeedSize();
    bool _newHDPrivateKey(const uint8_t* seed, size_t seedLength, uint32_t version, char** key, size_t* keyLength);
    bool _deriveHDPrivateKey(const char* parentPrivateKey, size_t index, bool isHardened, char** childPrivateKey, size_t* childPrivateKeyLength);
    CBitcoinResult _deriveHDPublicKey(const char* parentKey, size_t index, bool isHardened, uint32_t publicVersion, uint32_t privateVersion, char** childPublicKey, size_t* childPublicKeyLength);
    CBitcoinResult _toHDPublicKey(const char* privateKeyIn, uint32_t publicVersion, char** publicKeyOut, size_t* publicKeyLength);

#ifdef __cplusplus
}
#endif

#endif /* HDPrivateKey_hpp */

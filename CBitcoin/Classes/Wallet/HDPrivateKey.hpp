//
//  HDPrivateKey.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/30/18.
//
//  Copyright © 2018 Blockchain Commons.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#ifndef HDPrivateKey_hpp
#define HDPrivateKey_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    size_t _minimumSeedSize();
    CBitcoinResult _newHDPrivateKey(const uint8_t* seed, size_t seedLength, uint32_t version, char** key, size_t* keyLength);
    CBitcoinResult _deriveHDPrivateKey(const char* parentPrivateKey, size_t index, bool isHardened, char** childPrivateKey, size_t* childPrivateKeyLength);
    CBitcoinResult _deriveHDPublicKey(const char* parentKey, size_t index, bool isHardened, uint32_t publicVersion, uint32_t privateVersion, char** childPublicKey, size_t* childPublicKeyLength);
    CBitcoinResult _toHDPublicKey(const char* privateKeyIn, uint32_t publicVersion, char** publicKeyOut, size_t* publicKeyLength);

#ifdef __cplusplus
}
#endif

#endif /* HDPrivateKey_hpp */

//
//  HDKey.hpp
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

#ifndef HDKey_hpp
#define HDKey_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    size_t _minimumSeedSize(void);
    CBitcoinResult _newHDPrivateKey(const uint8_t* _Nonnull seed, size_t seedLength, uint32_t version, char* _Nullable * _Nonnull key, size_t* _Nonnull keyLength);
    CBitcoinResult _deriveHDPrivateKey(const char* _Nonnull parentPrivateKey, size_t index, bool isHardened, char* _Nullable * _Nonnull childPrivateKey, size_t* _Nonnull childPrivateKeyLength);
    CBitcoinResult _deriveHDPublicKey(const char* _Nonnull parentKey, size_t index, bool isHardened, uint32_t publicVersion, uint32_t privateVersion, char* _Nullable * _Nonnull childPublicKey, size_t* _Nonnull childPublicKeyLength);
    CBitcoinResult _toHDPublicKey(const char* _Nonnull privateKeyIn, uint32_t publicVersion, char* _Nullable * _Nonnull publicKeyOut, size_t* _Nonnull publicKeyLength);
    CBitcoinResult _toECKey(const char* _Nonnull hdKeyIn, uint32_t publicVersion, uint32_t privateVersion, bool* _Nonnull  isPrivate, uint8_t* _Nullable * _Nonnull ecKeyOut, size_t* _Nonnull ecKeyLength);

#ifdef __cplusplus
}
#endif

#endif /* HDKey_hpp */

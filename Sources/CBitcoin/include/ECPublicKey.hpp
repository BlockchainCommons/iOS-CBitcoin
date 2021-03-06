//
//  ECPublicKey.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 11/1/18.
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

#ifndef ECPublicKey_hpp
#define ECPublicKey_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    size_t _ecCompressedPublicKeySize(void);
    size_t _ecUncompressedPublicKeySize(void);

    CBitcoinResult _toECPublicKey(const uint8_t* _Nonnull privateKey, size_t privateKeyLength, bool isCompressed, uint8_t* _Nullable * _Nonnull publicKey, size_t* _Nonnull publicKeyLength);
    CBitcoinResult _toECPaymentAddress(const uint8_t* _Nonnull publicKey, size_t publicKeyLength, uint8_t version, char* _Nullable * _Nonnull address, size_t* _Nonnull addressLength);

    CBitcoinResult _compress(const uint8_t* _Nonnull uncompressedPublicKey, uint8_t* _Nullable * _Nonnull compressed, size_t* _Nonnull compressedLength);
    CBitcoinResult _decompress(const uint8_t* _Nonnull compressedPublicKey, uint8_t* _Nullable * _Nonnull uncompressed, size_t* _Nonnull uncompressedLength);

#ifdef __cplusplus
}
#endif

#endif /* ECPublicKey_hpp */

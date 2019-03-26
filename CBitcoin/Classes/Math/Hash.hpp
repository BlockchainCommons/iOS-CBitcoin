//
//  Hash.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/24/18.
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

#ifndef Hash_hpp
#define Hash_hpp

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    void _ripemd160(const uint8_t* _Nonnull data, size_t dataLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength);
    void _sha160(const uint8_t* _Nonnull data, size_t dataLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength);
    void _sha256(const uint8_t* _Nonnull data, size_t dataLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength);
    void _sha256HMAC(const uint8_t* _Nonnull data, size_t dataLength, const uint8_t* _Nonnull key, size_t keyLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength);
    void _sha512(const uint8_t* _Nonnull data, size_t dataLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength);
    void _sha512HMAC(const uint8_t* _Nonnull data, size_t dataLength, const uint8_t* _Nonnull key, size_t keyLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength);
    void _pkcs5PBKDF2HMACSHA512(const uint8_t* _Nonnull passphrase, size_t passphraseLength, const uint8_t* _Nonnull salt, size_t saltLengh, size_t iterations, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength);
    void _bitcoin256(const uint8_t* _Nonnull data, size_t dataLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength);
    void _bitcoin160(const uint8_t* _Nonnull data, size_t dataLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength);

#ifdef __cplusplus
}
#endif

#endif /* Hash_hpp */

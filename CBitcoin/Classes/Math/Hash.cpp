//
//  Hash.cpp
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

#include "Hash.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

void _ripemd160(const uint8_t* _Nonnull data, size_t dataLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto h = ripemd160_hash(d);
    _sendData(h, hash, hashLength);
}

void _sha160(const uint8_t* _Nonnull data, size_t dataLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto h = sha1_hash(d);
    _sendData(h, hash, hashLength);
}

void _sha256(const uint8_t* _Nonnull data, size_t dataLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto h = sha256_hash(d);
    _sendData(h, hash, hashLength);
}

void _sha256HMAC(const uint8_t* _Nonnull data, size_t dataLength, const uint8_t* _Nonnull key, size_t keyLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto k = _toDataSlice(key, keyLength);
    auto h = hmac_sha256_hash(d, k);
    _sendData(h, hash, hashLength);
}

void _sha512(const uint8_t* _Nonnull data, size_t dataLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto h = sha512_hash(d);
    _sendData(h, hash, hashLength);
}

void _sha512HMAC(const uint8_t* _Nonnull data, size_t dataLength, const uint8_t* _Nonnull key, size_t keyLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto k = _toDataSlice(key, keyLength);
    auto h = hmac_sha512_hash(d, k);
    _sendData(h, hash, hashLength);
}

void _pkcs5PBKDF2HMACSHA512(const uint8_t* _Nonnull passphrase, size_t passphraseLength, const uint8_t* _Nonnull salt, size_t saltLength, size_t iterations, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength) {
    auto p = _toDataSlice(passphrase, passphraseLength);
    auto s = _toDataSlice(salt, saltLength);
    auto h = pkcs5_pbkdf2_hmac_sha512(p, s, iterations);
    _sendData(h, hash, hashLength);
}

void _bitcoin256(const uint8_t* _Nonnull data, size_t dataLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto h = bitcoin_hash(d);
    _sendData(h, hash, hashLength);
}

void _bitcoin160(const uint8_t* _Nonnull data, size_t dataLength, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto h = bitcoin_short_hash(d);
    _sendData(h, hash, hashLength);
}

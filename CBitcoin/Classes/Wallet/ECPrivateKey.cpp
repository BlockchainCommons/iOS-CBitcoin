//
//  ECPrivateKey.cpp
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

#include "ECPrivateKey.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

size_t _ecPrivateKeySize(void) {
    return ec_secret_size;
}

CBitcoinResult _ecNewPrivateKey(const uint8_t* _Nonnull seed, size_t seedLength, uint8_t* _Nullable * _Nonnull privateKey, size_t* _Nonnull privateKeyLength) {
    if(seedLength < minimum_seed_size) {
        return CBITCOIN_ERROR_SEED_TOO_SMALL;
    }
    const auto seedChunk = _toDataChunk(seed, seedLength);
    const wallet::hd_private hdKey(seedChunk);
    const auto secret = hdKey.secret();
    if(secret == null_hash) {
        return CBITCOIN_ERROR_INVALID_SEED;
    }
    _sendData(secret, privateKey, privateKeyLength);
    return CBITCOIN_SUCCESS;
}

CBitcoinResult _ecPrivateKeyToWIF(const uint8_t* _Nonnull privateKey, size_t privateKeyLength, uint8_t wifVersion, bool isCompressed, char* _Nullable * _Nonnull wif, size_t* _Nonnull wifLength) {
    if(privateKeyLength != ec_secret_size) {
        return CBITCOIN_ERROR_INVALID_SEED_SIZE;
    }
    ec_secret secretKey;
    _toByteArray(secretKey, privateKey);
    const uint8_t paymentVersion = 0; // unused
    const auto version = wallet::ec_private::to_version(paymentVersion, wifVersion);
    const wallet::ec_private priv(secretKey, version, isCompressed);
    const auto wifString = priv.encoded();
    _sendString(wifString, wif, wifLength);
    return CBITCOIN_SUCCESS;
}

CBitcoinResult _wifToECPrivateKey(const char* _Nonnull wif, uint8_t* _Nullable * _Nonnull privateKey, size_t* _Nonnull privateKeyLength) {
    const auto wifString = std::string(wif);
    const wallet::ec_private priv(wifString, wallet::ec_private::mainnet_p2kh);
    const auto secret = priv.secret();
    if(secret == null_hash) {
        return CBITCOIN_ERROR_INVALID_SEED;
    }
    _sendData(secret, privateKey, privateKeyLength);
    return CBITCOIN_SUCCESS;
}

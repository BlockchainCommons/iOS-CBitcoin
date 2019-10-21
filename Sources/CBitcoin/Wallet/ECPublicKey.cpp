//
//  ECPublicKey.cpp
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

#include "ECPublicKey.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

size_t _ecCompressedPublicKeySize(void) {
    return ec_compressed_size;
}

size_t _ecUncompressedPublicKeySize(void) {
    return ec_uncompressed_size;
}

CBitcoinResult _toECPublicKey(const uint8_t* _Nonnull privateKey, size_t privateKeyLength, bool isCompressed, uint8_t* _Nullable * _Nonnull publicKey, size_t* _Nonnull publicKeyLength) {
    if(privateKeyLength != ec_secret_size) {
        return CBITCOIN_ERROR_INVALID_SEED_SIZE;
    }
    ec_secret secretKey;
    _toByteArray(secretKey, privateKey);
    ec_compressed point;
    secret_to_public(point, secretKey);
    const wallet::ec_public pub(point, isCompressed);
    data_chunk data;
    pub.to_data(data);
    _sendData(data, publicKey, publicKeyLength);
    return CBITCOIN_SUCCESS;
}

CBitcoinResult _toECPaymentAddress(const uint8_t* _Nonnull publicKey, size_t publicKeyLength, uint8_t version, char* _Nullable * _Nonnull address, size_t* _Nonnull addressLength) {
    if(publicKeyLength == ec_compressed_size) {
        ec_compressed point;
        _toByteArray(point, publicKey);
        const wallet::ec_public pub(point);
        const wallet::payment_address paymentAddress(pub, version);
        const auto encodedAddress = paymentAddress.encoded();
        _sendString(encodedAddress, address, addressLength);
        return CBITCOIN_SUCCESS;
    } else if(publicKeyLength == ec_uncompressed_size) {
        ec_uncompressed point;
        _toByteArray(point, publicKey);
        const wallet::ec_public pub(point);
        const wallet::payment_address paymentAddress(pub, version);
        const auto encodedAddress = paymentAddress.encoded();
        _sendString(encodedAddress, address, addressLength);
        return CBITCOIN_SUCCESS;
    }
    return CBITCOIN_ERROR_INVALID_SEED_SIZE;
}

CBitcoinResult _compress(const uint8_t* _Nonnull uncompressedPublicKey, uint8_t* _Nullable * _Nonnull compressed, size_t* _Nonnull compressedLength) {
    ec_uncompressed uncompressedKey;
    _toByteArray(uncompressedKey, uncompressedPublicKey);
    ec_compressed compressedKey;
    if(!compress(compressedKey, uncompressedKey)) {
        return CBITCOIN_ERROR_INVALID_KEY;
    }
    _sendData(compressedKey, compressed, compressedLength);
    return CBITCOIN_SUCCESS;
}

CBitcoinResult _decompress(const uint8_t* _Nonnull compressedPublicKey, uint8_t* _Nullable * _Nonnull uncompressed, size_t* _Nonnull uncompressedLength) {
    ec_compressed compressedKey;
    _toByteArray(compressedKey, compressedPublicKey);
    ec_uncompressed uncompressedKey;
    if(!decompress(uncompressedKey, compressedKey)) {
        return CBITCOIN_ERROR_INVALID_KEY;
    }
    _sendData(uncompressedKey, uncompressed, uncompressedLength);
    return CBITCOIN_SUCCESS;
}

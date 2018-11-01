//
//  ECNew.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/30/18.
//

#include "ECNew.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

#include <iostream>

using namespace libbitcoin;

size_t _ecPrivateKeySize() {
    return ec_secret_size;
}

size_t _ecCompressedPublicKeySize() {
    return ec_compressed_size;
}

size_t _ecUncompressedPublicKeySize() {
    return ec_uncompressed_size;
}

bool _ecNew(const uint8_t* seed, size_t seedLength, uint8_t** privateKey, size_t* privateKeyLength) {
    if(seedLength < minimum_seed_size) {
        return false;
    }
    const auto seedChunk = _toDataChunk(seed, seedLength);
    const wallet::hd_private hdKey(seedChunk);
    const auto secret = hdKey.secret();
    if(secret == null_hash) {
        return false;
    }
    _returnData(secret, privateKey, privateKeyLength);
    return true;
}

bool _ecToPublic(const uint8_t* privateKey, size_t privateKeyLength, bool isCompressed, uint8_t** publicKey, size_t* publicKeyLength) {
    if(privateKeyLength != ec_secret_size) {
        return false;
    }
    ec_secret secretKey;
    _toByteArray(secretKey, privateKey);
    ec_compressed point;
    secret_to_public(point, secretKey);
    const wallet::ec_public pub(point, isCompressed);
    data_chunk data;
    pub.to_data(data);
    _returnData(data, publicKey, publicKeyLength);
    return true;
}

bool _ecPublicToPaymentAddress(const uint8_t* publicKey, size_t publicKeyLength, uint8_t version, char** address, size_t* addressLength) {
    if(publicKeyLength == ec_compressed_size) {
        ec_compressed point;
        _toByteArray(point, publicKey);
        const wallet::ec_public pub(point);
        const wallet::payment_address paymentAddress(pub, version);
        const auto encodedAddress = paymentAddress.encoded();
        _returnString(encodedAddress, address, addressLength);
        return true;
    } else if(publicKeyLength == ec_uncompressed_size) {
        ec_uncompressed point;
        _toByteArray(point, publicKey);
        const wallet::ec_public pub(point);
        const wallet::payment_address paymentAddress(pub, version);
        const auto encodedAddress = paymentAddress.encoded();
        _returnString(encodedAddress, address, addressLength);
        return true;
    } else {
        return false;
    }
}

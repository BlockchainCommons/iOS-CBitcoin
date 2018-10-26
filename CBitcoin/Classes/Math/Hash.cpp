//
//  Hash.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/24/18.
//

#include "Hash.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

void _RIPEMD160Hash(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength) {
    data_slice d = _toDataSlice(data, dataLength);
    short_hash h = ripemd160_hash(d);
    _returnData(h, hash, hashLength);
}

void _SHA1Hash(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength) {
    data_slice d = _toDataSlice(data, dataLength);
    short_hash h = sha1_hash(d);
    _returnData(h, hash, hashLength);
}

void _SHA256Hash(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength) {
    data_slice d = _toDataSlice(data, dataLength);
    hash_digest h = sha256_hash(d);
    _returnData(h, hash, hashLength);
}

void _SHA256HMAC(const uint8_t* data, size_t dataLength, const uint8_t* key, size_t keyLength, uint8_t** hash, size_t* hashLength) {
    data_slice d = _toDataSlice(data, dataLength);
    data_slice k = _toDataSlice(key, keyLength);
    hash_digest h = hmac_sha256_hash(d, k);
    _returnData(h, hash, hashLength);
}

void _SHA512Hash(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength) {
    data_slice d = _toDataSlice(data, dataLength);
    long_hash h = sha512_hash(d);
    _returnData(h, hash, hashLength);
}

void _SHA512HMAC(const uint8_t* data, size_t dataLength, const uint8_t* key, size_t keyLength, uint8_t** hash, size_t* hashLength) {
    data_slice d = _toDataSlice(data, dataLength);
    data_slice k = _toDataSlice(key, keyLength);
    long_hash h = hmac_sha512_hash(d, k);
    _returnData(h, hash, hashLength);
}

void _PKCS5PBKDf2HMACSHA512(const uint8_t* passphrase, size_t passphraseLength, const uint8_t* salt, size_t saltLength, size_t iterations, uint8_t** hash, size_t* hashLength) {
    data_slice p = _toDataSlice(passphrase, passphraseLength);
    data_slice s = _toDataSlice(salt, saltLength);
    long_hash h = pkcs5_pbkdf2_hmac_sha512(p, s, iterations);
    _returnData(h, hash, hashLength);
}

void _bitcoinHash(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength) {
    data_slice d = _toDataSlice(data, dataLength);
    hash_digest h = bitcoin_hash(d);
    _returnData(h, hash, hashLength);
}

void _bitcoinShortHash(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength) {
    data_slice d = _toDataSlice(data, dataLength);
    short_hash h = bitcoin_short_hash(d);
    _returnData(h, hash, hashLength);
}

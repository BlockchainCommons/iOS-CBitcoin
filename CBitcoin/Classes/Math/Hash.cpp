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

void _ripemd160(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto h = ripemd160_hash(d);
    _returnData(h, hash, hashLength);
}

void _sha160(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto h = sha1_hash(d);
    _returnData(h, hash, hashLength);
}

void _sha256(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto h = sha256_hash(d);
    _returnData(h, hash, hashLength);
}

void _sha256HMAC(const uint8_t* data, size_t dataLength, const uint8_t* key, size_t keyLength, uint8_t** hash, size_t* hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto k = _toDataSlice(key, keyLength);
    auto h = hmac_sha256_hash(d, k);
    _returnData(h, hash, hashLength);
}

void _sha512(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto h = sha512_hash(d);
    _returnData(h, hash, hashLength);
}

void _sha512HMAC(const uint8_t* data, size_t dataLength, const uint8_t* key, size_t keyLength, uint8_t** hash, size_t* hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto k = _toDataSlice(key, keyLength);
    auto h = hmac_sha512_hash(d, k);
    _returnData(h, hash, hashLength);
}

void _pkcs5PBKDF2HMACSHA512(const uint8_t* passphrase, size_t passphraseLength, const uint8_t* salt, size_t saltLength, size_t iterations, uint8_t** hash, size_t* hashLength) {
    auto p = _toDataSlice(passphrase, passphraseLength);
    auto s = _toDataSlice(salt, saltLength);
    auto h = pkcs5_pbkdf2_hmac_sha512(p, s, iterations);
    _returnData(h, hash, hashLength);
}

void _bitcoin256(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto h = bitcoin_hash(d);
    _returnData(h, hash, hashLength);
}

void _bitcoin160(const uint8_t* data, size_t dataLength, uint8_t** hash, size_t* hashLength) {
    auto d = _toDataSlice(data, dataLength);
    auto h = bitcoin_short_hash(d);
    _returnData(h, hash, hashLength);
}

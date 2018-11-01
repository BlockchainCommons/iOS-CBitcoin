//
//  ECPrivateKey.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/30/18.
//

#include "ECPrivateKey.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

size_t _ecPrivateKeySize() {
    return ec_secret_size;
}

bool _ecNewPrivateKey(const uint8_t* seed, size_t seedLength, uint8_t** privateKey, size_t* privateKeyLength) {
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

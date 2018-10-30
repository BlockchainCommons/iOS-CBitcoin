//
//  ECNew.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/30/18.
//

#include "ECNew.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

bool _ecNew(const uint8_t* seed, size_t seedLength, uint8_t** key, size_t* keyLength) {
    if(seedLength < minimum_seed_size) {
        return false;
    }
    const auto seedChunk = _toDataChunk(seed, seedLength);
    const wallet::hd_private hdKey(seedChunk);
    const auto secret = hdKey.secret();
    if(secret == null_hash) {
        return false;
    }
    _returnData(secret, key, keyLength);
    return true;
}

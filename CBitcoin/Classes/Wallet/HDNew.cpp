//
//  HDNew.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/29/18.
//

#include "HDNew.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

size_t _minimumSeedSize() {
    return minimum_seed_size;
}

bool _hdNew(const uint8_t* seed, size_t seedLength, uint32_t version, char** key, size_t* keyLength) {
    if(seedLength < minimum_seed_size) {
        return false;
    }
    auto seedChunk = _toDataChunk(seed, seedLength);
    const auto prefixes = wallet::hd_private::to_prefixes(version, 0);
    const wallet::hd_private privateKey(seedChunk, prefixes);
    if(!privateKey) {
        return false;
    }
    auto hdKey = encode_base58(privateKey.to_hd_key());
    _returnString(hdKey, key, keyLength);
    return true;
}

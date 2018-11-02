//
//  HDPrivateKey.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/29/18.
//

#include "HDPrivateKey.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

size_t _minimumSeedSize() {
    return minimum_seed_size;
}

bool _newHDPrivateKey(const uint8_t* seed, size_t seedLength, uint32_t version, char** key, size_t* keyLength) {
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

bool _deriveHDPrivateKey(const char* parentPrivateKey, size_t index, bool isHardened, char** childPrivateKey, size_t* childPrivateKeyLength) {
    const auto parentPrivateString = std::string(parentPrivateKey);
    const auto parentPrivate = wallet::hd_private(parentPrivateString);
    if(!parentPrivate) {
        return false;
    }

    static constexpr auto firstHard = bc::wallet::hd_first_hardened_key;
    const auto position = isHardened ? firstHard + index : index;
    const auto childPrivate = parentPrivate.derive_private(position);
    if (!childPrivate) {
        return false;
    }

    const auto childPrivateString = childPrivate.encoded();
    _returnString(childPrivateString, childPrivateKey, childPrivateKeyLength);
    return true;
}

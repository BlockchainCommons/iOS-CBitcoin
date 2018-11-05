//
//  HDPrivateKey.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/29/18.
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

#include "HDPrivateKey.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

size_t _minimumSeedSize() {
    return minimum_seed_size;
}

CBitcoinResult _newHDPrivateKey(const uint8_t* seed, size_t seedLength, uint32_t version, char** key, size_t* keyLength) {
    if(seedLength < minimum_seed_size) {
        return CBITCOIN_ERROR_SEED_TOO_SMALL;
    }
    auto seedChunk = _toDataChunk(seed, seedLength);
    const auto prefixes = wallet::hd_private::to_prefixes(version, 0);
    const wallet::hd_private privateKey(seedChunk, prefixes);
    if(!privateKey) {
        return CBITCOIN_ERROR_INVALID_SEED;
    }
    auto hdKey = encode_base58(privateKey.to_hd_key());
    _sendString(hdKey, key, keyLength);
    return CBITCOIN_SUCCESS;
}

CBitcoinResult _deriveHDPrivateKey(const char* parentPrivateKey, size_t index, bool isHardened, char** childPrivateKey, size_t* childPrivateKeyLength) {
    const auto parentPrivateString = std::string(parentPrivateKey);
    const auto parentPrivate = wallet::hd_private(parentPrivateString);
    if(!parentPrivate) {
        return CBITCOIN_ERROR_INVALID_FORMAT;
    }

    static constexpr auto firstHard = wallet::hd_first_hardened_key;
    const auto position = isHardened ? firstHard + index : index;
    const auto childPrivate = parentPrivate.derive_private(position);
    if (!childPrivate) {
        return CBITCOIN_ERROR_INVALID_KEY;
    }

    const auto childPrivateString = childPrivate.encoded();
    _sendString(childPrivateString, childPrivateKey, childPrivateKeyLength);
    return CBITCOIN_SUCCESS;
}

CBitcoinResult _deriveHDPublicKey(const char* parentKey, size_t index, bool isHardened, uint32_t publicVersion, uint32_t privateVersion, char** childPublicKey, size_t* childPublicKeyLength) {
    const std::string parentKeyString(parentKey);
    data_chunk parentKeyData;
    if (!decode_base58(parentKeyData, parentKeyString) || parentKeyData.size() != wallet::hd_key_size) {
        return CBITCOIN_ERROR_INVALID_FORMAT;
    }

    wallet::hd_key key;
    std::copy(parentKeyData.begin(), parentKeyData.end(), key.begin());
    uint32_t keyVersion = from_big_endian_unsafe<uint32_t>(key.begin());
    if (keyVersion != privateVersion && keyVersion != publicVersion) {
        return CBITCOIN_ERROR_INVALID_VERSION;
    }

    if (isHardened && keyVersion != privateVersion) {
        return CBITCOIN_ERROR_PRIVATE_KEY_REQUIRED;
    }

    if (keyVersion == privateVersion) {
        const auto prefixes = wallet::hd_private::to_prefixes(privateVersion, publicVersion);

        // Derive the public key from new private key and the public version.
        const wallet::hd_private privateKey(key, prefixes);
        if(!privateKey) {
            return CBITCOIN_ERROR_INVALID_KEY;
        }
        static constexpr auto firstHard = wallet::hd_first_hardened_key;
        const auto position = isHardened ? firstHard + index : index;

        const auto childPubKey = privateKey.derive_public(position);
        if(!childPubKey) {
            return CBITCOIN_ERROR_INVALID_KEY;
        }
        const auto childPublicKeyString = childPubKey.encoded();
        _sendString(childPublicKeyString, childPublicKey, childPublicKeyLength);
        return CBITCOIN_SUCCESS;
    } else {
        // Derive the public key from new private key and the public version.
        const wallet::hd_public publicKey(key, publicVersion);
        if(!publicKey) {
            return CBITCOIN_ERROR_INVALID_KEY;
        }
        const auto childPubKey = publicKey.derive_public(index);
        if(!childPubKey) {
            return CBITCOIN_ERROR_INVALID_KEY;
        }
        const auto childPublicKeyString = childPubKey.encoded();
        _sendString(childPublicKeyString, childPublicKey, childPublicKeyLength);
        return CBITCOIN_SUCCESS;
    }
}

CBitcoinResult _toHDPublicKey(const char* privateKeyIn, uint32_t publicVersion, char** publicKeyOut, size_t* publicKeyLength) {
    const std::string privateKeyString(privateKeyIn);
    wallet::hd_private privateKey(privateKeyString);
    const auto privateHDKey = privateKey.to_hd_key();

    const auto privateVersion = bc::wallet::hd_private::to_prefix(privateKey.lineage().prefixes);
    const auto prefixes = wallet::hd_private::to_prefixes(privateVersion, publicVersion);
    const wallet::hd_private versioned(privateHDKey, prefixes);

    if(!versioned) {
        return CBITCOIN_ERROR_INVALID_KEY;
    }

    const auto publicKey = versioned.to_public().encoded();
    _sendString(publicKey, publicKeyOut, publicKeyLength);
    return CBITCOIN_SUCCESS;
}

CBitcoinResult _toECKey(const char* hdKeyIn, uint32_t publicVersion, uint32_t privateVersion, bool* isPrivate, uint8_t** ecKeyOut, size_t* ecKeyLength) {
    const std::string hdKey(hdKeyIn);
    data_chunk hdKeyData;
    if (!decode_base58(hdKeyData, hdKey) || hdKeyData.size() != wallet::hd_key_size) {
        return CBITCOIN_ERROR_INVALID_FORMAT;
    }

    wallet::hd_key key;
    std::copy(hdKeyData.begin(), hdKeyData.end(), key.begin());
    uint32_t keyVersion = from_big_endian_unsafe<uint32_t>(key.begin());
    if (keyVersion != privateVersion && keyVersion != publicVersion) {
        return CBITCOIN_ERROR_INVALID_VERSION;
    }

    if (keyVersion == privateVersion) {
        const auto prefixes = wallet::hd_private::to_prefixes(privateVersion, publicVersion);

        const wallet::hd_private privateKey(key, prefixes);
        if(!privateKey) {
            return CBITCOIN_ERROR_INVALID_KEY;
        }

        *isPrivate = true;
        const auto secret = privateKey.secret();
        _sendData(secret, ecKeyOut, ecKeyLength);
        return CBITCOIN_SUCCESS;
    } else {
        const auto publicKey = wallet::hd_public(key, publicVersion);
        if(!publicKey) {
            return CBITCOIN_ERROR_INVALID_KEY;
        }

        *isPrivate = false;
        const auto ecPublic = wallet::ec_public(publicKey);
        data_chunk ecPublicData;
        ecPublic.to_data(ecPublicData);
        _sendData(ecPublicData, ecKeyOut, ecKeyLength);
        return CBITCOIN_SUCCESS;
    }
}

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

CBitcoinResult _ecNewPrivateKey(const uint8_t* seed, size_t seedLength, uint8_t** privateKey, size_t* privateKeyLength) {
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

CBitcoinResult _ecPrivateKeyToWIF(const uint8_t* privateKey, size_t privateKeyLength, uint8_t wifVersion, bool isCompressed, char** wif, size_t* wifLength) {
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

CBitcoinResult _wifToECPrivateKey(const char* wif, uint8_t** privateKey, size_t* privateKeyLength) {
    const auto wifString = std::string(wif);
    const wallet::ec_private priv(wifString, wallet::ec_private::mainnet_p2kh);
    const auto secret = priv.secret();
    if(secret == null_hash) {
        return CBITCOIN_ERROR_INVALID_SEED;
    }
    _sendData(secret, privateKey, privateKeyLength);
    return CBITCOIN_SUCCESS;
}

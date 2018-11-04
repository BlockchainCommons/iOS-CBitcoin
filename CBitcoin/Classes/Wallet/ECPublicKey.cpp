//
//  ECPublicKey.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 11/1/18.
//

#include "ECPublicKey.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

size_t _ecCompressedPublicKeySize() {
    return ec_compressed_size;
}

size_t _ecUncompressedPublicKeySize() {
    return ec_uncompressed_size;
}

CBitcoinResult _toECPublicKey(const uint8_t* privateKey, size_t privateKeyLength, bool isCompressed, uint8_t** publicKey, size_t* publicKeyLength) {
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

CBitcoinResult _toECPaymentAddress(const uint8_t* publicKey, size_t publicKeyLength, uint8_t version, char** address, size_t* addressLength) {
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

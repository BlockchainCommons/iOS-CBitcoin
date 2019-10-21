//
//  PaymentAddress.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 11/5/18.
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

#include "PaymentAddress.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

void _addressEncode(const uint8_t* _Nonnull ripemd160, uint8_t version, char* _Nullable * _Nonnull paymentAddress, size_t* _Nonnull paymentAddressLength) {
    short_hash hashArray;
    _toByteArray(hashArray, ripemd160);
    const wallet::payment_address address(hashArray, version);
    const auto addressString = address.encoded();
    _sendString(addressString, paymentAddress, paymentAddressLength);
}

CBitcoinResult _addressDecode(const char* _Nonnull address, uint8_t* _Nonnull version, uint8_t* _Nullable * _Nonnull payload, size_t* _Nonnull payloadLength, uint32_t* _Nonnull checksum) {
    const auto paymentAddress = wallet::payment_address(std::string(address));
    if(!paymentAddress) {
        return CBITCOIN_ERROR_INVALID_ADDRESS;
    }
    const auto payment = paymentAddress.to_payment();
    short_hash payld;
    unwrap(*version, payld, *checksum, payment);
    _sendData(payld, payload, payloadLength);
    return CBITCOIN_SUCCESS;
}

void _addressEmbed(const uint8_t* _Nonnull data, size_t dataLength, uint8_t version, char* _Nullable * _Nonnull paymentAddress, size_t* _Nonnull paymentAddressLength) {
    auto dataChunk = _toDataChunk(data, dataLength);

    // Create script from hash of data.
    const auto ops = chain::script::to_pay_key_hash_pattern(ripemd160_hash(dataChunk));
    const auto script = chain::script(std::move(ops));

    // Make ripemd hash of serialized script.
    const auto hash = ripemd160_hash(script.to_data(false));

    // Make address (money sent here is lost forever).
    const auto address = wallet::payment_address(hash, version);
    const auto addressString = address.encoded();
    _sendString(addressString, paymentAddress, paymentAddressLength);
}

CBitcoinResult _addressHash(const char* _Nonnull address, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength) {
    const auto paymentAddress = wallet::payment_address(std::string(address));
    if(!paymentAddress) {
        return CBITCOIN_ERROR_INVALID_ADDRESS;
    }
    const auto h = paymentAddress.hash();
    _sendData(h, hash, hashLength);
    return CBITCOIN_SUCCESS;
}

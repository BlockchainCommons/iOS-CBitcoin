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

void _addressEncode(const uint8_t* ripemd160, uint8_t version, char** paymentAddress, size_t* paymentAddressLength) {
    short_hash hashArray;
    _toByteArray(hashArray, ripemd160);
    const wallet::payment_address address(hashArray, version);
    const auto addressString = address.encoded();
    _sendString(addressString, paymentAddress, paymentAddressLength);
}

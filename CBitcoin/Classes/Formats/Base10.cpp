//
//  Base10.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/24/18.
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

#include "Base10.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

uint8_t _btcDecimalPlaces() {
    return btc_decimal_places;
}

uint8_t _mbtcDecimalPlaces() {
    return mbtc_decimal_places;
}

uint8_t _ubtcDecimalPlaces() {
    return ubtc_decimal_places;
}

void _base10Encode(uint64_t amount, char** string, size_t* stringLength, uint8_t decimalPlaces) {
    auto s = encode_base10(amount, decimalPlaces);
    _sendString(s, string, stringLength);
}

CBitcoinResult _base10Decode(const char* string, uint64_t* amount, size_t decimalPlaces, bool strict) {
    auto s = std::string(string);
    return decode_base10(*amount, s, static_cast<uint8_t>(decimalPlaces), strict) ? CBITCOIN_SUCCESS : CBITCOIN_ERROR_INVALID_FORMAT;
}

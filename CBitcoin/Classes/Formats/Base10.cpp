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

uint8_t _btcDecimalPlaces(void) {
    return btc_decimal_places;
}

uint8_t _mbtcDecimalPlaces(void) {
    return mbtc_decimal_places;
}

uint8_t _ubtcDecimalPlaces(void) {
    return ubtc_decimal_places;
}

void _encodeBase10(uint64_t amount, char* _Nullable * _Nonnull string, size_t* _Nonnull stringLength, uint8_t decimalPlaces) {
    auto s = encode_base10(amount, decimalPlaces);
    _sendString(s, string, stringLength);
}

CBitcoinResult _decodeBase10(const char* _Nonnull string, uint64_t* _Nonnull amount, size_t decimalPlaces, bool strict) {
    auto s = std::string(string);
    return decode_base10(*amount, s, static_cast<uint8_t>(decimalPlaces), strict) ? CBITCOIN_SUCCESS : CBITCOIN_ERROR_INVALID_FORMAT;
}

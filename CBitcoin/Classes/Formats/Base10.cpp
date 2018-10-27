//
//  Base10.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/24/18.
//

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

void _encodeBase10(uint64_t amount, char** string, size_t* stringLength, uint8_t decimalPlaces) {
    auto s = encode_base10(amount, decimalPlaces);
    _returnString(s, string, stringLength);
}

bool _decodeBase10(const char* string, uint64_t* amount, size_t decimalPlaces, bool strict) {
    auto s = std::string(string);
    return decode_base10(*amount, s, static_cast<uint8_t>(decimalPlaces), strict);
}

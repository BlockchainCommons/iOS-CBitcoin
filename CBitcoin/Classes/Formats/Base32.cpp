//
//  Base32.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/27/18.
//

#include "Base32.hpp"
#include <bitcoin/bitcoin.hpp>
#include <string>
#include "Util.hpp"

using namespace libbitcoin;

void _base32Encode(const char* prefix, const uint8_t* payload, size_t payloadLength, char** string, size_t* stringLength) {
    base32 b32 { std::string(prefix), _toDataChunk(payload, payloadLength) };
    auto encoded = encode_base32(b32);
    _sendString(encoded, string, stringLength);
}

CBitcoinResult _base32Decode(const char* string, char** prefix, size_t* prefixLength, uint8_t** payload, size_t* payloadLength) {
    auto s = std::string(string);
    auto b32 = base32();
    if(decode_base32(b32, s)) {
        _sendString(b32.prefix, prefix, prefixLength);
        _sendData(b32.payload, payload, payloadLength);
        return CBITCOIN_SUCCESS;
    } else {
        *prefix = NULL;
        *payload = NULL;
        return CBITCOIN_ERROR_INVALID_FORMAT;
    }
}

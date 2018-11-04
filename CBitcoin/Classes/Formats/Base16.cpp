//
//  Base16.cpp
//  Bitcoin
//
//  Created by Wolf McNally on 10/24/18.
//

#include "Base16.hpp"
#include <bitcoin/bitcoin.hpp>
#include <string>
#include "Util.hpp"

using namespace libbitcoin;

void _base16Encode(const uint8_t* data, size_t length, char** string, size_t* stringLength) {
    auto s = encode_base16(_toDataSlice(data, length));
    _sendString(s, string, stringLength);
}

CBitcoinResult _base16Decode(const char* string, uint8_t** data, size_t* dataLength) {
    auto s = std::string(string);
    auto chunk = data_chunk();
    if(decode_base16(chunk, s)) {
        _sendData(chunk, data, dataLength);
        return CBITCOIN_SUCCESS;
    } else {
        return CBITCOIN_ERROR_INVALID_FORMAT;
    }
}

void _bitcoinHashEncode(const uint8_t* data, char** string, size_t* stringLength) {
    auto s = encode_hash(_toHashDigest(data));
    _sendString(s, string, stringLength);
}

CBitcoinResult _bitcoinHashDecode(const char* string, uint8_t** data, size_t* dataLength) {
    auto s = std::string(string);
    auto hash = hash_digest();
    if(decode_hash(hash, s)) {
        _sendData(hash, data, dataLength);
        return CBITCOIN_SUCCESS;
    } else {
        return CBITCOIN_ERROR_INVALID_FORMAT;
    }
}

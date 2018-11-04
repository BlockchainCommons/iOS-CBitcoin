//
//  Base64.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/25/18.
//

#include "Base64.hpp"
#include <bitcoin/bitcoin.hpp>
#include <string>
#include "Util.hpp"

using namespace libbitcoin;

void _base64Encode(const uint8_t* data, size_t length, char** string, size_t* stringLength) {
    auto s = encode_base64(_toDataSlice(data, length));
    _sendString(s, string, stringLength);
}

CBitcoinResult _base64Decode(const char* string, uint8_t** data, size_t* dataLength) {
    auto s = std::string(string);
    auto chunk = data_chunk();
    if(!decode_base64(chunk, s)) {
        return CBITCOIN_ERROR_INVALID_FORMAT;
    }
    _sendData(chunk, data, dataLength);
    return CBITCOIN_SUCCESS;
}

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

void _encodeBase64(const uint8_t* data, size_t length, char** string, size_t* stringLength) {
    std::string s = encode_base64(_toDataSlice(data, length));
    _returnString(s, string, stringLength);
}

void _decodeBase64(const char* string, uint8_t** data, size_t* dataLength) {
    std::string s = std::string(string);
    data_chunk chunk = data_chunk();
    if(decode_base64(chunk, s)) {
        return _returnData(chunk, data, dataLength);
    } else {
        *data = NULL;
    }
}

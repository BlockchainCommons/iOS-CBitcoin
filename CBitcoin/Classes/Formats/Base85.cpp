//
//  Base85.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/25/18.
//

#include "Base85.hpp"
#include <bitcoin/bitcoin.hpp>
#include <string>
#include "Util.hpp"

using namespace libbitcoin;

void _encodeBase85(const uint8_t* data, size_t length, char** string, size_t* stringLength) {
    auto s = encode_base64(_toDataSlice(data, length));
    _returnString(s, string, stringLength);
}

void _decodeBase85(const char* string, uint8_t** data, size_t* dataLength) {
    auto s = std::string(string);
    auto chunk = data_chunk();
    if(decode_base64(chunk, s)) {
        return _returnData(chunk, data, dataLength);
    } else {
        *data = NULL;
    }
}

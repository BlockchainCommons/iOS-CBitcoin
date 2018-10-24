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

void _encodeBase16(const uint8_t* data, size_t length, char** string, size_t* stringLength) {
    std::string s = encode_base16(_toDataSlice(data, length));
    _returnString(s, string, stringLength);
}

void _decodeBase16(const char* string, uint8_t** data, size_t* dataLength) {
    std::string s = std::string(string);
    data_chunk chunk = data_chunk();
    if(decode_base16(chunk, s)) {
        return _returnData(chunk, data, dataLength);
    } else {
        *data = NULL;
    }
}

void _encodeHash(const uint8_t* data, char** string, size_t* stringLength) {
    std::string s = encode_hash(_toHashDigest(data));
    _returnString(s, string, stringLength);
}

void _decodeHash(const char* string, uint8_t** data, size_t* dataLength) {
    std::string s = std::string(string);
    hash_digest hash = hash_digest();
    if(decode_hash(hash, s)) {
        return _returnData(hash, data, dataLength);
    } else {
        *data = NULL;
    }
}

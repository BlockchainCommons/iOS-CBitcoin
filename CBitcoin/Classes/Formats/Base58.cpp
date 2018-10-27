//
//  Base58.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/22/18.
//  Copyright © 2018 Arciem LLC. All rights reserved.
//

#include "Base58.hpp"
#include <bitcoin/bitcoin.hpp>
#include <string>
#include "Util.hpp"

using namespace libbitcoin;

bool _isBase58Char(char c) {
    return is_base58(c);
}

bool _isBase58String(const char* string) {
    return is_base58(std::string(string));
}

void _encodeBase58(const uint8_t* data, size_t length, char** string, size_t* stringLength) {
    auto s = encode_base58(_toDataSlice(data, length));
    _returnString(s, string, stringLength);
}

void _decodeBase58(const char* string, uint8_t** data, size_t* dataLength) {
    auto s = std::string(string);
    auto chunk = data_chunk();
    if(decode_base58(chunk, s)) {
        return _returnData(chunk, data, dataLength);
    } else {
        *data = NULL;
    }
}

void _encodeBase58Check(const uint8_t* data, size_t length, uint8_t version, char** string, size_t* stringLength) {
    auto payload = _toDataSlice(data, length);
    auto wrapped = wrap(version, payload);
    auto s = encode_base58(wrapped);
    _returnString(s, string, stringLength);
}

//void _decodeBase58Check(const char* string, uint8_t** data, size_t* dataLength, uint8_t* version) {
//    auto s = std::string(string);
//    auto chunk = data_chunk();
//    if(decode_base58(chunk, s)) {
//        unwrap(*version, chunk, checksum, <#data_slice wrapped#>)
//        return _returnData(chunk, data, dataLength);
//    } else {
//        *data = NULL;
//    }
//}

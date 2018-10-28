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

void _base58Encode(const uint8_t* data, size_t length, char** string, size_t* stringLength) {
    auto s = encode_base58(_toDataSlice(data, length));
    _returnString(s, string, stringLength);
}

void _base58Decode(const char* string, uint8_t** data, size_t* dataLength) {
    auto s = std::string(string);
    auto chunk = data_chunk();
    if(decode_base58(chunk, s)) {
        return _returnData(chunk, data, dataLength);
    } else {
        *data = NULL;
    }
}

void _base58CheckEncode(const uint8_t* data, size_t length, uint8_t version, char** string, size_t* stringLength) {
    auto bytes = to_chunk(version);
    auto payload = _toDataChunk(data, length);
    extend_data(bytes, payload);
    append_checksum(bytes);
    auto s = encode_base58(bytes);
    _returnString(s, string, stringLength);
}

void _base58CheckDecode(const char* string, uint8_t** data, size_t* dataLength, uint8_t* version) {
    auto s = std::string(string);
    if(s.length() == 0) {
        *data = NULL;
        return;
    }
    auto chunk = data_chunk();
    if(decode_base58(chunk, s)) {
        *version = chunk[0];
        auto slice = data_slice(&*chunk.begin(), &*chunk.end());
        if(verify_checksum(slice)) {
            return _returnData(chunk, data, dataLength);
        } else {
            *data = NULL;
        }
    } else {
        *data = NULL;
    }
}

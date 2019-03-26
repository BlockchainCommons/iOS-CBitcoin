//
//  Base16.cpp
//  Bitcoin
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

#include "Base16.hpp"
#include <bitcoin/bitcoin.hpp>
#include <string>
#include "Util.hpp"

using namespace libbitcoin;

void _encodeBase16(const uint8_t* _Nonnull data, size_t length, char* _Nullable * _Nonnull string, size_t* _Nonnull stringLength) {
    auto s = encode_base16(_toDataSlice(data, length));
    _sendString(s, string, stringLength);
}

CBitcoinResult _decodeBase16(const char* _Nonnull string, uint8_t* _Nullable * _Nonnull data, size_t* _Nonnull dataLength) {
    auto s = std::string(string);
    auto chunk = data_chunk();
    if(decode_base16(chunk, s)) {
        _sendData(chunk, data, dataLength);
        return CBITCOIN_SUCCESS;
    } else {
        return CBITCOIN_ERROR_INVALID_FORMAT;
    }
}

void _encodeBitcoinHash(const uint8_t* _Nonnull data, char* _Nullable * _Nonnull string, size_t* _Nonnull stringLength) {
    auto s = encode_hash(_toHashDigest(data));
    _sendString(s, string, stringLength);
}

CBitcoinResult _decodeBitcoinHash(const char* _Nonnull string, uint8_t* _Nullable * _Nonnull data, size_t* _Nonnull dataLength) {
    auto s = std::string(string);
    auto hash = hash_digest();
    if(decode_hash(hash, s)) {
        _sendData(hash, data, dataLength);
        return CBITCOIN_SUCCESS;
    } else {
        return CBITCOIN_ERROR_INVALID_FORMAT;
    }
}

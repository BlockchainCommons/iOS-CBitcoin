//
//  Base32.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/27/18.
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

#include "Base32.hpp"
#include <bitcoin/bitcoin.hpp>
#include <string>
#include "Util.hpp"

using namespace libbitcoin;

void _encodeBase32(const char* prefix, const uint8_t* payload, size_t payloadLength, char** string, size_t* stringLength) {
    base32 b32 { std::string(prefix), _toDataChunk(payload, payloadLength) };
    auto encoded = encode_base32(b32);
    _sendString(encoded, string, stringLength);
}

CBitcoinResult _decodeBase32(const char* string, char** prefix, size_t* prefixLength, uint8_t** payload, size_t* payloadLength) {
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

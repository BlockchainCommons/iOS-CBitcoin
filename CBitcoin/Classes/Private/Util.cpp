//
//  Util.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/23/18.
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

#include "Util.hpp"

using namespace libbitcoin;

void _sendString(std::string s, char* _Nullable * _Nonnull string, size_t* _Nonnull stringLength) {
    *stringLength = s.length();
    *string = static_cast<char*>(malloc(*stringLength));
    s.copy(*string, *stringLength);
}

void _sendData(const data_chunk& chunk, uint8_t* _Nullable * _Nonnull data, size_t* _Nonnull dataLength) {
    *dataLength = chunk.size();
    *data = static_cast<uint8_t*>(malloc(*dataLength));
    std::copy(chunk.begin(), chunk.end(), *data);
}

data_slice _toDataSlice(const uint8_t* _Nonnull data, uint32_t length) {
    return data_slice(data, data + length);
}

data_chunk _toDataChunk(const uint8_t* _Nonnull data, uint32_t length) {
    return data_chunk(data, data + length);
}

hash_digest _toHashDigest(const uint8_t* _Nonnull data) {
    hash_digest d;
    for(hash_digest::iterator cur = d.begin(); cur != d.end();) {
        *cur++ = *data++;
    }
    return d;
}

short_hash _toShortHash(const uint8_t* _Nonnull data) {
    short_hash d;
    for(short_hash::iterator cur = d.begin(); cur != d.end();) {
        *cur++ = *data++;
    }
    return d;
}

ec_secret _toECSecret(const uint8_t* _Nonnull data) {
    ec_secret s;
    for(ec_secret::iterator cur = s.begin(); cur != s.end();) {
        *cur++ = *data++;
    }
    return s;
}

ec_signature _toECSignature(const uint8_t* _Nonnull data) {
    ec_signature s;
    for(ec_secret::iterator cur = s.begin(); cur != s.end();) {
        *cur++ = *data++;
    }
    return s;
}

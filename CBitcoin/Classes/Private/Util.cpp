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

void _sendString(std::string s, char** string, size_t* stringLength) {
    *stringLength = s.length();
    *string = static_cast<char*>(malloc(*stringLength));
    s.copy(*string, *stringLength);
}

void _sendData(const data_chunk& chunk, uint8_t** data, size_t* dataLength) {
    *dataLength = chunk.size();
    *data = static_cast<uint8_t*>(malloc(*dataLength));
    std::copy(chunk.begin(), chunk.end(), *data);
}

data_slice _toDataSlice(const uint8_t* data, uint32_t length) {
    return data_slice(data, data + length);
}

data_chunk _toDataChunk(const uint8_t* data, uint32_t length) {
    return data_chunk(data, data + length);
}

//template <size_t Size>
//std::array<uint8_t, Size> _toArray(const uint8_t* data) {
//    return std::array<uint8_t, Size>(data, data + Size);
//}

hash_digest _toHashDigest(const uint8_t* data) {
    hash_digest d;
    for(hash_digest::iterator cur = d.begin(); cur != d.end();) {
        *cur++ = *data++;
    }
    return d;
}

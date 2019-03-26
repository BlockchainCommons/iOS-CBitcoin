//
//  Util.hpp
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

#ifndef Util_hpp
#define Util_hpp

#include <bitcoin/bitcoin.hpp>

void _sendString(std::string s, char* _Nullable * _Nonnull string, size_t* _Nonnull stringLength);
void _sendData(const libbitcoin::data_chunk& chunk, uint8_t* _Nullable * _Nonnull data, size_t* _Nonnull dataLength);

libbitcoin::data_slice _toDataSlice(const uint8_t* _Nonnull data, uint32_t length);

libbitcoin::data_chunk _toDataChunk(const uint8_t* _Nonnull data, uint32_t length);

//template <size_t Size>
//std::array<uint8_t, Size> _toArray(const uint8_t* _Nonnull data);

libbitcoin::hash_digest _toHashDigest(const uint8_t* _Nonnull data);
libbitcoin::short_hash _toShortHash(const uint8_t* _Nonnull data);
libbitcoin::ec_secret _toECSecret(const uint8_t* _Nonnull data);
libbitcoin::ec_signature _toECSignature(const uint8_t* _Nonnull data);

template<size_t SIZE>
void _sendData(const libbitcoin::byte_array<SIZE>& hash, uint8_t* _Nullable * _Nonnull data, size_t* _Nonnull dataLength) {
    *dataLength = hash.size();
    *data = static_cast<uint8_t*>(malloc(*dataLength));
    std::copy(hash.begin(), hash.end(), *data);
}

template<size_t SIZE>
void _toByteArray(libbitcoin::byte_array<SIZE>& array, const uint8_t* _Nonnull bytes) {
    auto p = bytes;
    for(typename libbitcoin::byte_array<SIZE>::iterator i = array.begin(); i != array.end();) {
        *i++ = *p++;
    }
}

template<typename T, typename U>
std::vector<T> _receiveInstances(const U* const* instances, size_t count) {
    std::vector<T> list;
    for(auto index = 0; index < count; index++) {
        const auto& value = *(T*)instances[index];
        list.push_back(value);
    }
    return list;
}

template<typename T, typename U>
void _sendInstances(std::vector<T> list, U*** instances, size_t* _Nonnull count) {
    *count = list.size();
    *instances = static_cast<U**>(malloc(*count * sizeof(U*)));
    auto instancesArray = *instances;
    int index = 0;
    for(const auto& i: list) {
        instancesArray[index++] = (U*)new T(i);
    }
}
#endif /* PrivateUtil_hpp */

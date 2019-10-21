//
//  WrappedData.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 11/6/18.
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

#include "WrappedData.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

void _wrapEncode(const uint8_t* _Nonnull data, size_t dataLength, uint8_t version, uint8_t* _Nullable * _Nonnull wrappedData, size_t* _Nonnull wrappedDataLength) {
    data_chunk payload = _toDataChunk(data, dataLength);
    auto bytes = to_chunk(version);
    extend_data(bytes, payload);
    append_checksum(bytes);
    _sendData(bytes, wrappedData, wrappedDataLength);
}

CBitcoinResult _wrapDecode(const uint8_t* _Nonnull wrappedData, size_t wrappedDataLength, uint8_t* _Nonnull version, uint8_t* _Nullable * _Nonnull payload, size_t* _Nonnull payloadLength, uint32_t* _Nonnull checksum) {
    data_slice wrapped = _toDataSlice(wrappedData, wrappedDataLength);
    if(!verify_checksum(wrapped)) {
        return CBITCOIN_ERROR_INVALID_CHECKSUM;
    }
    data_chunk wrappedChunk = _toDataChunk(wrappedData, wrappedDataLength);
    auto i = wrappedChunk.begin();
    *version = *i++;
    auto payloadSize = wrappedDataLength - sizeof(uint32_t) - 1;
    data_chunk payloadChunk = _toDataChunk(&*i, payloadSize);
    _sendData(payloadChunk, payload, payloadLength);
    i += payloadSize;
    *checksum = from_little_endian_unsafe<uint32_t>(i);
    return CBITCOIN_SUCCESS;
}

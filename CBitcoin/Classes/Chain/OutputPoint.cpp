//
//  OutputPoint.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 11/7/18.
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

#include "OutputPoint.hpp"
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"
#include <sstream>

using namespace libbitcoin;
using namespace chain;

_outputPoint* _Nonnull _outputPointNew() {
    return reinterpret_cast<_outputPoint*>(new output_point);
}

_outputPoint* _Nonnull _outputPointCopy(_outputPoint* _Nonnull instance) {
    const auto& self = *reinterpret_cast<output_point*>(instance);
    auto* copy = new output_point(self);
    return reinterpret_cast<_outputPoint*>(copy);
}

CBitcoinResult _outputPointFromData(const uint8_t * data, size_t dataLength, _outputPoint** instance) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    auto* i = new output_point();
    if(!i->from_data(dataChunk)) {
        return CBITCOIN_ERROR_INVALID_DATA;
    }
    *instance = reinterpret_cast<_outputPoint*>(i);
    return CBITCOIN_SUCCESS;
}

void _outputPointToData(_outputPoint* _Nonnull instance, uint8_t** data, size_t* dataLength) {
    const auto& self = *reinterpret_cast<output_point*>(instance);
    const auto dataChunk = self.to_data();
    _sendData(dataChunk, data, dataLength);
}

bool _outputPointIsValid(_outputPoint* _Nonnull instance) {
    const auto& self = *reinterpret_cast<const output_point*>(instance);
    return self.is_valid();
}

bool _outputPointEqual(_outputPoint* _Nonnull instance1, _outputPoint* _Nonnull instance2) {
    const auto& lhs = *reinterpret_cast<const output_point*>(instance1);
    const auto& rhs = *reinterpret_cast<const output_point*>(instance2);
    return lhs == rhs;
}

uint32_t _outputPointGetIndex(_outputPoint* _Nonnull instance) {
    const auto& self = *reinterpret_cast<const output_point*>(instance);
    return self.index();
}

void _outputPointSetIndex(_outputPoint* _Nonnull instance, uint32_t index) {
    auto& self = *reinterpret_cast<output_point*>(instance);
    self.set_index(index);
}

void _outputPointGetHash(_outputPoint* _Nonnull instance, uint8_t** hash, size_t* hashLength) {
    const auto& self = *reinterpret_cast<const output_point*>(instance);
    _sendData(self.hash(), hash, hashLength);
}

void _outputPointSetHash(_outputPoint* _Nonnull instance, const uint8_t* hash) {
    auto& self = *reinterpret_cast<output_point*>(instance);
    auto hashDigest = _toHashDigest(hash);
    self.set_hash(hashDigest);
}

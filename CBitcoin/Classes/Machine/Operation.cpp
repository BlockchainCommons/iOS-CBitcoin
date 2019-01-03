//
//  Operation.cpp
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

#include "Operation.hpp"
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"
#include <sstream>

using namespace libbitcoin;
using namespace machine;

_operation* _Nonnull _operationNew(void) {
    auto* i = new operation();
    return reinterpret_cast<_operation*>(i);
}

_operation* _Nonnull _operationFromOpcode(uint8_t opcode) {
    const auto op = static_cast<machine::opcode>(opcode);
    auto* i = new operation(op);
    return reinterpret_cast<_operation*>(i);
}

CBitcoinResult _operationFromData(const uint8_t* data, size_t dataLength, bool isMinimal, _operation** instance) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    auto* i = new operation(dataChunk, isMinimal);
    *instance = reinterpret_cast<_operation*>(i);
    return CBITCOIN_SUCCESS;
}

CBitcoinResult _operationDeserialize(const uint8_t* data, size_t dataLength, _operation** instance) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    auto* i = new operation();
    if(!i->from_data(dataChunk)) {
        return CBITCOIN_ERROR_INVALID_DATA;
    }
    *instance = reinterpret_cast<_operation*>(i);
    return CBITCOIN_SUCCESS;
}

void _operationSerialize(_operation* _Nonnull instance, uint8_t** data, size_t* dataLength) {
    const auto& self = *reinterpret_cast<operation*>(instance);
    const auto dataChunk = self.to_data();
    _sendData(dataChunk, data, dataLength);
}

CBitcoinResult _operationFromString(const char* string, _operation** instance) {
    const auto str = std::string(string);
    auto* i = new operation();
    if(!i->from_string(str)) {
        return CBITCOIN_ERROR_INVALID_SCRIPT;
    }
    *instance = reinterpret_cast<_operation*>(i);
    return CBITCOIN_SUCCESS;
}

void _operationToString(_operation* _Nonnull instance, uint32_t activeRules, char** string, size_t* stringLength) {
    const auto& self = *reinterpret_cast<operation*>(instance);
    const auto str = self.to_string(activeRules);
    _sendString(str, string, stringLength);
}

bool _operationIsValid(_operation* _Nonnull instance) {
    const auto& self = *reinterpret_cast<operation*>(instance);
    return self.is_valid();
}

bool _operationEqual(_operation* _Nonnull instance1, _operation* _Nonnull instance2) {
    const auto& lhs = *reinterpret_cast<operation*>(instance1);
    const auto& rhs = *reinterpret_cast<operation*>(instance2);
    return lhs == rhs;
}

uint8_t _operationGetOpcode(_operation* _Nonnull instance) {
    const auto& self = *reinterpret_cast<operation*>(instance);
    return static_cast<uint8_t>(self.code());
}

void _operationGetData(_operation* _Nonnull instance, uint8_t** data, size_t *dataLength) {
    const auto& self = *reinterpret_cast<operation*>(instance);
    const auto dataChunk = self.data();
    _sendData(dataChunk, data, dataLength);
}

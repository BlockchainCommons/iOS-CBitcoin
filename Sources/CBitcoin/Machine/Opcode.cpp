//
//  Opcode.cpp
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

#include "Opcode.hpp"
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sstream>
#include "Util.hpp"

using namespace libbitcoin;
using namespace chain;

void _opcodeToString(uint8_t opcode, uint32_t activeRules, char* _Nullable * _Nonnull string, size_t* _Nonnull stringLength) {
    const auto op = machine::opcode(opcode);
    const auto rules = static_cast<machine::rule_fork>(activeRules);
    const auto str = opcode_to_string(op, rules);
    _sendString(str, string, stringLength);
}

CBitcoinResult _opcodeFromString(const char* _Nonnull string, uint8_t* _Nonnull opcode) {
    const auto str = std::string(string);
    machine::opcode op;
    if(!opcode_from_string(op, str)) {
        return CBITCOIN_ERROR_INVALID_OPCODE;
    }
    *opcode = static_cast<uint8_t>(op);
    return CBITCOIN_SUCCESS;
}

void _opcodeToHexadecimal(uint8_t opcode, char* _Nullable * _Nonnull string, size_t* _Nonnull stringLength) {
    const auto op = machine::opcode(opcode);
    const auto str = opcode_to_hexadecimal(op);
    _sendString(str, string, stringLength);
}

CBitcoinResult _opcodeFromHexadecimal(const char* _Nonnull string, uint8_t* _Nonnull opcode) {
    const auto str = std::string(string);
    machine::opcode op;
    if(!opcode_from_hexadecimal(op, str)) {
        return CBITCOIN_ERROR_INVALID_OPCODE;
    }
    *opcode = static_cast<uint8_t>(op);
    return CBITCOIN_SUCCESS;
}

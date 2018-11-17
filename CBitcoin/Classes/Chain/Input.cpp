//
//  Input.cpp
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

#include "Input.hpp"
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sstream>
#include "Util.hpp"

using namespace libbitcoin;
using namespace chain;

_input* _Nonnull _inputNew() {
    return reinterpret_cast<_input*>(new input);
}

_input* _Nonnull _inputCopy(_input* _Nonnull instance) {
    const auto& self = *reinterpret_cast<input*>(instance);
    auto* copy = new input(self);
    return reinterpret_cast<_input*>(copy);
}

CBitcoinResult _inputDeserialize(const uint8_t* data, size_t dataLength, _input** instance) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    auto* i = new input();
    if(!i->from_data(dataChunk)) {
        return CBITCOIN_ERROR_INVALID_DATA;
    }
    *instance = reinterpret_cast<_input*>(i);
    return CBITCOIN_SUCCESS;
}

void _inputSerialize(_input* _Nonnull instance, uint8_t** data, size_t* dataLength) {
    const auto& self = *reinterpret_cast<input*>(instance);
    const auto dataChunk = self.to_data();
    _sendData(dataChunk, data, dataLength);
}

bool _inputEqual(_input* _Nonnull instance1, _input* _Nonnull instance2) {
    const auto& lhs = *reinterpret_cast<input*>(instance1);
    const auto& rhs = *reinterpret_cast<input*>(instance2);
    return lhs == rhs;
}

_outputPoint* _Nonnull _inputGetPreviousOutput(_input* _Nonnull const instance) {
    const auto& self = *reinterpret_cast<input*>(instance);
    output_point* outputPointInstance = new output_point(self.previous_output());
    return reinterpret_cast<_outputPoint*>(outputPointInstance);
}

void _inputSetPreviousOutput(_input* _Nonnull instance, _outputPoint* _Nonnull outputPointInstance) {
    auto& self = *reinterpret_cast<input*>(instance);
    const auto& o = *reinterpret_cast<const output_point*>(outputPointInstance);
    self.set_previous_output(o);
}

_script* _Nonnull _inputGetScript(_input* _Nonnull instance) {
    const auto& self = *reinterpret_cast<input*>(instance);
    auto* script = new chain::script(self.script());
    return reinterpret_cast<_script*>(script);
}

void _inputSetScript(_input* _Nonnull instance, _script* _Nonnull scriptInstance) {
    auto& self = *reinterpret_cast<input*>(instance);
    const auto& s = *reinterpret_cast<const script*>(scriptInstance);
    self.set_script(s);
}

uint32_t _inputGetSequence(_input* _Nonnull instance) {
    const auto& self = *reinterpret_cast<input*>(instance);
    return self.sequence();
}

void _inputSetSequence(_input* _Nonnull instance, uint32_t sequence) {
    auto& self = *reinterpret_cast<input*>(instance);
    self.set_sequence(sequence);
}

void _inputGetScriptString(_input* _Nonnull instance, uint32_t activeRules, char** decoded, size_t* decodedLength) {
    const auto& self = *reinterpret_cast<input*>(instance);
    const auto script = self.script();
    const auto decodedString = script.to_string(activeRules);
    _sendString(decodedString, decoded, decodedLength);
}

bool _inputIsValid(_input* _Nonnull instance) {
    const auto& self = *reinterpret_cast<const input*>(instance);
    return self.is_valid();
}

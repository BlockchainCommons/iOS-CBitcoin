//
//  Script.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 11/7/18.
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

#include "Script.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;
using namespace chain;

void _scriptDecode(const uint8_t* data, size_t dataLength, char** decoded, size_t* decodedLength) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    const auto script = chain::script(dataChunk, false);
    const auto decodedString = script.to_string(machine::rule_fork::all_rules);
    _sendString(decodedString, decoded, decodedLength);
}

CBitcoinResult _scriptEncode(const char* script, uint8_t** encoded, size_t* encodedLength) {
    const auto scriptString = std::string(script);
    chain::script s;
    if(!s.from_string(scriptString)) {
        return CBITCOIN_ERROR_INVALID_SCRIPT;
    }
    
    const auto encodedData = s.to_data(false);
    _sendData(encodedData, encoded, encodedLength);
    return CBITCOIN_SUCCESS;
}

CBitcoinResult _scriptToAddress(const char* script, uint8_t version, char** paymentAddress, size_t* paymentAddressLength) {
    const auto scriptString = std::string(script);
    chain::script s;
    if(!s.from_string(scriptString)) {
        return CBITCOIN_ERROR_INVALID_SCRIPT;
    }

    const wallet::payment_address address(s, version);
    _sendString(address.encoded(), paymentAddress, paymentAddressLength);
    return CBITCOIN_SUCCESS;
}

_script* _Nonnull _scriptNew() {
    return reinterpret_cast<_script*>(new script);
}

_script* _Nonnull _scriptCopy(_script* _Nonnull instance) {
    const auto& self = *reinterpret_cast<script*>(instance);
    auto* copy = new script(self);
    return reinterpret_cast<_script*>(copy);
}

CBitcoinResult _scriptFromString(const char* string, _script** instance) {
    const auto str = std::string(string);
    auto* i = new script();
    if(!i->from_string(str)) {
        return CBITCOIN_ERROR_INVALID_SCRIPT;
    }
    *instance = reinterpret_cast<_script*>(i);
    return CBITCOIN_SUCCESS;
}

CBitcoinResult _scriptFromData(const uint8_t* data, size_t dataLength, bool prefix, _script** instance) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    auto* i = new script();
    if(!i->from_data(dataChunk, prefix)) {
        return CBITCOIN_ERROR_INVALID_DATA;
    }
    *instance = reinterpret_cast<_script*>(i);
    return CBITCOIN_SUCCESS;
}

void _scriptToData(_script* _Nonnull instance, bool prefix, uint8_t** data, size_t* dataLength) {
    const auto& self = *reinterpret_cast<script*>(instance);
    const auto dataChunk = self.to_data(prefix);
    _sendData(dataChunk, data, dataLength);
}

bool _scriptIsValid(_script* _Nonnull instance) {
    const auto& self = *reinterpret_cast<const script*>(instance);
    return self.is_valid();
}

bool _scriptEqual(_script* _Nonnull instance1, _script* _Nonnull instance2) {
    const auto& lhs = *reinterpret_cast<const script*>(instance1);
    const auto& rhs = *reinterpret_cast<const script*>(instance2);
    return lhs == rhs;
}

//
//  Output.cpp
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

#include "Output.hpp"
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sstream>
#include "Util.hpp"
#include "Input.hpp"

using namespace libbitcoin;
using namespace chain;

_output* _Nonnull _outputNew() {
    return (_output*)new output;
}

_output* _Nonnull _outputCopy(_output* _Nonnull instance) {
    const auto& self = *reinterpret_cast<output*>(instance);
    auto* copy = new output(self);
    return reinterpret_cast<_output*>(copy);
}

CBitcoinResult _outputDeserialize(const uint8_t* data, size_t dataLength, _output** instance) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    auto* o = new output();
    if(!o->from_data(dataChunk)) {
        return CBITCOIN_ERROR_INVALID_DATA;
    }
    *instance = reinterpret_cast<_output*>(o);
    return CBITCOIN_SUCCESS;
}

void _outputSerialize(_output* _Nonnull instance, uint8_t** data, size_t* dataLength) {
    const auto& self = *reinterpret_cast<output*>(instance);
    const auto dataChunk = self.to_data();
    _sendData(dataChunk, data, dataLength);
}

bool _outputEqual(_output* _Nonnull instance1, _output* _Nonnull instance2) {
    const auto& lhs = *reinterpret_cast<output*>(instance1);
    const auto& rhs = *reinterpret_cast<output*>(instance2);
    return lhs == rhs;
}

CBitcoinResult _outputSetPaymentAddress(_output* _Nonnull instance, const char* address) {
    auto& self = *reinterpret_cast<output*>(instance);

    const auto paymentAddress = wallet::payment_address(std::string(address));
    if(!paymentAddress) {
        return CBITCOIN_ERROR_INVALID_ADDRESS;
    }
    const auto payment = paymentAddress.to_payment();
    short_hash hash;
    uint8_t version;
    unwrap(version, hash, payment);
    auto ops = chain::script::to_pay_key_hash_pattern(hash);
    auto script = chain::script(ops);

    self.set_script(script);
    return CBITCOIN_SUCCESS;
}

uint64_t _outputGetValue(_output* _Nonnull instance) {
    const auto& self = *reinterpret_cast<output*>(instance);
    return self.value();
}

void _outputSetValue(_output* _Nonnull instance, uint64_t value) {
    auto& self = *reinterpret_cast<output*>(instance);
    self.set_value(value);
}

void _outputGetScriptString(_output* _Nonnull instance, uint32_t activeRules, char** decoded, size_t* decodedLength) {
    const auto& self = *reinterpret_cast<output*>(instance);

    const auto script = self.script();
    const auto decodedString = script.to_string(activeRules);
    _sendString(decodedString, decoded, decodedLength);
}

_script* _Nonnull _outputGetScript(_output* _Nonnull instance) {
    const auto& self = *reinterpret_cast<output*>(instance);
    auto* script = new chain::script(self.script());
    return reinterpret_cast<_script*>(script);
}

void _outputSetScript(_output* _Nonnull instance, _script* _Nonnull scriptInstance) {
    auto& self = *reinterpret_cast<output*>(instance);
    const auto& s = *reinterpret_cast<const script*>(scriptInstance);
    self.set_script(s);
}

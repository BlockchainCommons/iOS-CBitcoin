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

CBitcoinResult _scriptDeserialize(const uint8_t* data, size_t dataLength, bool prefix, _script** instance) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    auto* i = new script();
    if(!i->from_data(dataChunk, prefix)) {
        return CBITCOIN_ERROR_INVALID_DATA;
    }
    *instance = reinterpret_cast<_script*>(i);
    return CBITCOIN_SUCCESS;
}

_script* _Nonnull _scriptFromOperations(const _operation* const _Nonnull * operations, size_t operationsCount) {
    const auto list = _receiveInstances<machine::operation, _operation>(operations, operationsCount);
    auto* i = new script(list);
    return reinterpret_cast<_script*>(i);
}

void _scriptSerialize(_script* _Nonnull instance, bool prefix, uint8_t** data, size_t* dataLength) {
    const auto& self = *reinterpret_cast<script*>(instance);
    const auto dataChunk = self.to_data(prefix);
    _sendData(dataChunk, data, dataLength);
}

size_t _scriptSerializedSize(_script* _Nonnull instance, bool prefix) {
    const auto& self = *reinterpret_cast<script*>(instance);
    return self.serialized_size(prefix);
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

void _scriptGetOperations(_script* _Nonnull instance, _operation* _Nonnull ** _Nonnull operations, size_t* _Nonnull operationsCount) {
    const auto& self = *reinterpret_cast<script*>(instance);
    _sendInstances(self.operations(), operations, operationsCount);
}

bool _scriptIsEmpty(_script* _Nonnull instance) {
    const auto& self = *reinterpret_cast<const script*>(instance);
    return self.empty();
}

void _scriptClear(_script* _Nonnull instance) {
    auto& self = *reinterpret_cast<script*>(instance);
    self.clear();
}

void _scriptGetWitnessProgram(_script* _Nonnull instance, uint8_t** program, size_t* programLength) {
    const auto& self = *reinterpret_cast<const script*>(instance);
    const auto chunk = self.witness_program();
    _sendData(chunk, program, programLength);
}

int _scriptGetVersion(_script* _Nonnull instance) {
    const auto& self = *reinterpret_cast<const script*>(instance);
    return static_cast<int>(self.version());
}

int _scriptGetPattern(_script* _Nonnull instance) {
    const auto& self = *reinterpret_cast<const script*>(instance);
    return static_cast<int>(self.pattern());
}

int _scriptGetInputPattern(_script* _Nonnull instance) {
    const auto& self = *reinterpret_cast<const script*>(instance);
    return static_cast<int>(self.input_pattern());
}

int _scriptGetOutputPattern(_script* _Nonnull instance) {
    const auto& self = *reinterpret_cast<const script*>(instance);
    return static_cast<int>(self.output_pattern());
}

void _scriptMakePayNullDataPattern(const uint8_t* data, size_t dataLength, _operation* _Nonnull ** _Nonnull operations, size_t* _Nonnull operationsCount) {
    const auto slice = _toDataSlice(data, dataLength);
    const auto ops = script::to_pay_null_data_pattern(slice);
    _sendInstances(ops, operations, operationsCount);
}

uint32_t _scriptVerify(_transaction* _Nonnull transactionInstance, uint32_t inputIndex, uint32_t rules, _script* _Nonnull prevoutScriptInstance, uint64_t value) {
    const auto& tx = *reinterpret_cast<const transaction*>(transactionInstance);
    const auto& scr = *reinterpret_cast<const script*>(prevoutScriptInstance);
    const code c = script::verify(tx, inputIndex, rules, scr, value);
    return c.value();
}

void _generateSignatureHash(_transaction* _Nonnull transactionInstance, uint32_t inputIndex, _script* _Nonnull scriptInstance, uint8_t sigHashType, int32_t scriptVersion, uint64_t value, uint8_t** hash, size_t* hashLength) {
    const auto& tx = *reinterpret_cast<const transaction*>(transactionInstance);
    const auto& scr = *reinterpret_cast<const script*>(scriptInstance);
    const auto ver = static_cast<script::script_version>(scriptVersion);
    const auto h = script::generate_signature_hash(tx, inputIndex, scr, sigHashType, ver, value);
    _sendData(h, hash, hashLength);
}

bool _checkSignature(const uint8_t* _Nonnull signature, uint8_t sigHashType, const uint8_t* _Nonnull publicKey, size_t publicKeyLength, _script* _Nonnull scriptInstance, _transaction* _Nonnull transactionInstance, uint32_t inputIndex, int32_t scriptVersion, uint64_t value) {
    ec_signature sig;
    _toByteArray(sig, signature);
    const auto key = _toDataChunk(publicKey, publicKeyLength);
    const auto& scr = *reinterpret_cast<const script*>(scriptInstance);
    const auto& tx = *reinterpret_cast<const transaction*>(transactionInstance);
    const auto ver = static_cast<script::script_version>(scriptVersion);
    return script::check_signature(sig, sigHashType, key, scr, tx, inputIndex, ver, value);
}

CBitcoinResult _createEndorsement(const uint8_t* _Nonnull ecPrivateKey, _script* _Nonnull scriptInstance, _transaction* _Nonnull transactionInstance, uint32_t inputIndex, uint8_t sigHashType, int32_t scriptVersion, uint64_t value, uint8_t** endorsement, size_t* endorsementLength) {
    ec_secret secret;
    _toByteArray(secret, ecPrivateKey);
    const auto& scr = *reinterpret_cast<const script*>(scriptInstance);
    const auto& tx = *reinterpret_cast<const transaction*>(transactionInstance);
    const auto ver = static_cast<script::script_version>(scriptVersion);
    libbitcoin::endorsement en;
    if (!script::create_endorsement(en, secret, scr, tx, inputIndex, sigHashType, ver, value)) {
        return CBITCOIN_ERROR_INVALID_SIGNATURE;
    }
    _sendData(en, endorsement, endorsementLength);
    return CBITCOIN_SUCCESS;
}

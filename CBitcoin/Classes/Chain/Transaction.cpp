//
//  Transaction.cpp
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

#include "Transaction.hpp"
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"
#include <sstream>

using namespace libbitcoin;
using namespace chain;

CBitcoinResult _transactionDecode(const uint8_t* data, size_t dataLength, bool isPretty, char** decoded, size_t* decodedLength) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    transaction tx;
    if(!tx.from_data(dataChunk)) {
        return CBITCOIN_ERROR_INVALID_TRANSACTION;
    }
    const auto ptree = property_tree(tx, true);
    std::stringstream o;
    boost::property_tree::write_json(o, ptree, isPretty);
    _sendString(o.str(), decoded, decodedLength);
    return CBITCOIN_SUCCESS;
}

    // MARK: - OutputPoint

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

bool _outputPointIsValid(_outputPoint* _Nonnull instance) {
    const auto& self = *reinterpret_cast<const output_point*>(instance);
    return self.is_valid();
}

bool _outputPointEqual(_outputPoint* _Nonnull instance1, _outputPoint* _Nonnull instance2) {
    const auto& lhs = *reinterpret_cast<const output_point*>(instance1);
    const auto& rhs = *reinterpret_cast<const output_point*>(instance2);
    return lhs == rhs;
}

    // MARK: - Input

_input* _Nonnull _inputNew() {
    return reinterpret_cast<_input*>(new input);
}

_input* _Nonnull _inputCopy(_input* _Nonnull instance) {
    const auto& self = *reinterpret_cast<input*>(instance);
    auto* copy = new input(self);
    return reinterpret_cast<_input*>(copy);
}

CBitcoinResult _inputFromData(const uint8_t* data, size_t dataLength, _input** instance) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    auto* i = new input();
    if(!i->from_data(dataChunk)) {
        return CBITCOIN_ERROR_INVALID_DATA;
    }
    *instance = reinterpret_cast<_input*>(i);
    return CBITCOIN_SUCCESS;
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

uint32_t _inputGetSequence(_input* _Nonnull instance) {
    const auto& self = *reinterpret_cast<input*>(instance);
    return self.sequence();
}

void _inputSetSequence(_input* _Nonnull instance, uint32_t sequence) {
    auto& self = *reinterpret_cast<input*>(instance);
    self.set_sequence(sequence);
}

void _inputGetScript(_input* _Nonnull instance, char** decoded, size_t* decodedLength) {
    const auto& self = *reinterpret_cast<input*>(instance);
    const auto script = self.script();
    const auto decodedString = script.to_string(machine::rule_fork::all_rules);
    _sendString(decodedString, decoded, decodedLength);
}

    // MARK: - Output

_output* _Nonnull _outputNew() {
    return (_output*)new output;
}

_output* _Nonnull _outputCopy(_output* _Nonnull instance) {
    const auto& self = *reinterpret_cast<output*>(instance);
    auto* copy = new output(self);
    return reinterpret_cast<_output*>(copy);
}

CBitcoinResult _outputFromData(const uint8_t* data, size_t dataLength, _output** instance) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    auto* o = new output();
    if(!o->from_data(dataChunk)) {
        return CBITCOIN_ERROR_INVALID_DATA;
    }
    *instance = reinterpret_cast<_output*>(o);
    return CBITCOIN_SUCCESS;
}

bool _outputEqual(_output* _Nonnull instance1, _input* _Nonnull instance2) {
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

void _outputGetScript(_output* _Nonnull instance, char** decoded, size_t* decodedLength) {
    const auto& self = *reinterpret_cast<output*>(instance);

    const auto script = self.script();
    const auto decodedString = script.to_string(machine::rule_fork::all_rules);
    _sendString(decodedString, decoded, decodedLength);
}

    // MARK: - Transaction

_transaction* _Nonnull _transactionNew() {
    return (_transaction*)new transaction;
}

_transaction* _Nonnull _transactionCopy(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    auto* copy = new transaction(self);
    return reinterpret_cast<_transaction*>(copy);
}

CBitcoinResult _transactionFromData(const uint8_t* data, size_t dataLength, _transaction** instance) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    auto* t = new transaction();
    if(!t->from_data(dataChunk)) {
        return CBITCOIN_ERROR_INVALID_DATA;
    }
    *instance = reinterpret_cast<_transaction*>(t);
    return CBITCOIN_SUCCESS;
}

void _transactionToData(_transaction* _Nonnull instance, uint8_t** data, size_t* dataLength) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    const auto dataChunk = self.to_data();
    _sendData(dataChunk, data, dataLength);
}

bool _transactionIsValid(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.is_valid();
}

bool _transactionIsCoinbase(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.is_coinbase();
}

uint32_t _transactionGetVersion(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.version();
}

void _transactionSetVersion(_transaction* _Nonnull instance, uint32_t version) {
    auto& self = *reinterpret_cast<transaction*>(instance);
    self.set_version(version);
}

uint32_t _transactionGetLockTime(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.locktime();
}

void _transactionSetLockTime(_transaction* _Nonnull instance, uint32_t lockTime) {
    auto& self = *reinterpret_cast<transaction*>(instance);
    self.set_locktime(lockTime);
}

void _transactionSetInputs(_transaction* _Nonnull instance, const _input* const _Nonnull * inputs, size_t inputsCount) {
    auto& self = *reinterpret_cast<transaction*>(instance);
    input::list list = _receiveInstances<input, _input>(inputs, inputsCount);
    self.set_inputs(list);
}

void _transactionGetInputs(_transaction* _Nonnull instance, _input* _Nonnull ** _Nonnull inputs, size_t* _Nonnull inputsCount) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    _sendInstances(self.inputs(), inputs, inputsCount);
}

void _transactionSetOutputs(_transaction* _Nonnull instance, const _output* const _Nonnull * outputs, size_t outputsCount) {
    auto& self = *reinterpret_cast<transaction*>(instance);
    output::list list = _receiveInstances<output, _output>(outputs, outputsCount);
    self.set_outputs(list);
}

void _transactionGetOutputs(_transaction* _Nonnull instance, _output* _Nonnull ** _Nonnull outputs, size_t* _Nonnull outputsCount) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    _sendInstances(self.outputs(), outputs, outputsCount);
}

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
#include <sstream>
#include "Util.hpp"

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

_transaction* _Nonnull _transactionNew() {
    return (_transaction*)new transaction;
}

_transaction* _Nonnull _transactionCopy(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    auto* copy = new transaction(self);
    return reinterpret_cast<_transaction*>(copy);
}

CBitcoinResult _transactionDeserialize(const uint8_t* data, size_t dataLength, _transaction** instance) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    auto* t = new transaction();
    if(!t->from_data(dataChunk)) {
        return CBITCOIN_ERROR_INVALID_DATA;
    }
    *instance = reinterpret_cast<_transaction*>(t);
    return CBITCOIN_SUCCESS;
}

void _transactionSerialize(_transaction* _Nonnull instance, uint8_t** data, size_t* dataLength) {
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

bool _transactionIsOversizedCoinbase(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.is_oversized_coinbase();
}

bool _transactionIsNullNonCoinbase(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.is_null_non_coinbase();
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
    const auto list = _receiveInstances<input, _input>(inputs, inputsCount);
    self.set_inputs(list);
}

void _transactionGetInputs(_transaction* _Nonnull instance, _input* _Nonnull ** _Nonnull inputs, size_t* _Nonnull inputsCount) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    _sendInstances(self.inputs(), inputs, inputsCount);
}

void _transactionSetOutputs(_transaction* _Nonnull instance, const _output* const _Nonnull * outputs, size_t outputsCount) {
    auto& self = *reinterpret_cast<transaction*>(instance);
    const auto list = _receiveInstances<output, _output>(outputs, outputsCount);
    self.set_outputs(list);
}

void _transactionGetOutputs(_transaction* _Nonnull instance, _output* _Nonnull ** _Nonnull outputs, size_t* _Nonnull outputsCount) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    _sendInstances(self.outputs(), outputs, outputsCount);
}

bool _transactionIsFinal(_transaction* _Nonnull instance, size_t blockHeight, uint32_t blockTime) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.is_final(blockHeight, blockTime);
}

bool _transactionIsLocked(_transaction* _Nonnull instance, size_t blockHeight, uint32_t medianTimePast) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.is_locked(blockHeight, medianTimePast);
}

bool _transactionIsLockTimeConflict(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.is_locktime_conflict();
}

size_t _transactionSerializedSize(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.serialized_size();
}

void _transactionHash(_transaction* _Nonnull instance, uint8_t** hash, size_t* hashLength) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    const auto h = self.hash();
    _sendData(h, hash, hashLength);
}

uint64_t _transactionTotalInputValue(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.total_input_value();
}

uint64_t _transactionTotalOutputValue(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.total_output_value();
}

bool _transactionIsOverspent(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.is_overspent();
}

size_t _transactionSignatureOperationsCount(_transaction* _Nonnull instance, bool bip16, bool bip141) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.signature_operations(bip16, bip141);
}

bool _transactionIsMissingPreviousOutputs(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.is_missing_previous_outputs();
}

bool _transactionIsConfirmedDoubleSpend(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.is_confirmed_double_spend();
}

bool _transactionIsDusty(_transaction* _Nonnull instance, uint64_t minimumOutputValue) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.is_dusty(minimumOutputValue);
}

bool _transactionIsMature(_transaction* _Nonnull instance, size_t height) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.is_mature(height);
}

bool _transactionIsInternalDoubleSpend(_transaction* _Nonnull instance) {
    const auto& self = *reinterpret_cast<transaction*>(instance);
    return self.is_internal_double_spend();
}

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

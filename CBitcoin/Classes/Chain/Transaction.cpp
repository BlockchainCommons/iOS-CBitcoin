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
    return (_outputPoint*)new output_point;
}

void _outputPointDelete(_outputPoint* _Nonnull op) {
    delete op;
}

uint32_t _outputPointGetIndex(_outputPoint* _Nonnull op) {
    auto& self = *(output_point*)op;
    return self.index();
}

void _outputPointSetIndex(_outputPoint* _Nonnull op, uint32_t index) {
    auto& self = *(output_point*)op;
    self.set_index(index);
}

void _outputPointGetHash(_outputPoint* _Nonnull op, uint8_t** hash, size_t* hashLength) {
    auto& self = *(output_point*)op;
    _sendData(self.hash(), hash, hashLength);
}

void _outputPointSetHash(_outputPoint* _Nonnull op, const uint8_t* hash) {
    auto& self = *(output_point*)op;
    auto hashDigest = _toHashDigest(hash);
    self.set_hash(hashDigest);
}

    // MARK: - Input

_input* _Nonnull _inputNew() {
    return (_input*)new input;
}

void _inputDelete(_input* _Nonnull i) {
    delete i;
}

_outputPoint* _Nonnull _inputGetPreviousOutput(_input* _Nonnull i) {
    auto& self = *(input*)i;
    auto& op = self.previous_output();
    return (_outputPoint*)&op;
}

void _inputSetPreviousOutput(_input* _Nonnull i, _outputPoint* _Nonnull op) {
    auto& self = *(input*)i;
    auto& o = *(output_point*)op;
    self.set_previous_output(o);
}

uint32_t _inputGetSequence(_input* _Nonnull i) {
    auto& self = *(input*)i;
    return self.sequence();
}

void _inputSetSequence(_input* _Nonnull i, uint32_t sequence) {
    auto& self = *(input*)i;
    self.set_sequence(sequence);
}

    // MARK: - Output

_output* _Nonnull _outputNew() {
    return (_output*)new output;
}

void _outputDelete(_output* _Nonnull o) {
    delete o;
}

CBitcoinResult _outputSetPaymentAddress(_output* _Nonnull o, const char* address) {
    auto& self = *(output*)o;

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

uint64_t _outputGetValue(_output* _Nonnull o) {
    auto& self = *(output*)o;
    return self.value();
}

void _outputSetValue(_output* _Nonnull o, uint64_t value) {
    auto& self = *(output*)o;
    self.set_value(value);
}

void _outputGetScript(_output* _Nonnull o, char** decoded, size_t* decodedLength) {
    auto& self = *(output*)o;

    const auto script = self.script();
    const auto decodedString = script.to_string(machine::rule_fork::all_rules);
    _sendString(decodedString, decoded, decodedLength);
}

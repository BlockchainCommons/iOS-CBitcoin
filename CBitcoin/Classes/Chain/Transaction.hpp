//
//  Transaction.hpp
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

#ifndef Transaction_hpp
#define Transaction_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    CBitcoinResult _transactionDecode(const uint8_t* data, size_t dataLength, bool isPretty, char** decoded, size_t* decodedLength);

    typedef struct _outputPoint _outputPoint;
    _outputPoint* _Nonnull _outputPointNew();
    _outputPoint* _Nonnull _outputPointCopy(_outputPoint* _Nonnull instance);
    uint32_t _outputPointGetIndex(_outputPoint* _Nonnull instance);
    void _outputPointSetIndex(_outputPoint* _Nonnull instance, uint32_t index);
    void _outputPointGetHash(_outputPoint* _Nonnull instance, uint8_t** hash, size_t* hashLength);
    void _outputPointSetHash(_outputPoint* _Nonnull instance, const uint8_t* hash);

    typedef struct _input _input;
    _input* _Nonnull _inputNew();
    _input* _Nonnull _inputCopy(_input* _Nonnull instance);
    _outputPoint* _Nonnull _inputGetPreviousOutput(_input* _Nonnull const instance);
    void _inputSetPreviousOutput(_input* _Nonnull instance, _outputPoint* _Nonnull outputPointInstance);
    uint32_t _inputGetSequence(_input* _Nonnull instance);
    void _inputSetSequence(_input* _Nonnull instance, uint32_t sequence);

    typedef struct _output _output;
    _output* _Nonnull _outputNew();
    _output* _Nonnull _outputCopy(_output* _Nonnull instance);
    CBitcoinResult _outputSetPaymentAddress(_output* _Nonnull instance, const char* address);
    uint64_t _outputGetValue(_output* _Nonnull instance);
    void _outputSetValue(_output* _Nonnull instance, uint64_t value);
    void _outputGetScript(_output* _Nonnull instance, char** decoded, size_t* decodedLength);

    typedef struct _transaction _transaction;
    _transaction* _Nonnull _transactionNew();
    _transaction* _Nonnull _transactionCopy(_transaction* _Nonnull instance);
    uint32_t _transactionGetVersion(_transaction* _Nonnull instance);
    void _transactionSetVersion(_transaction* _Nonnull instance, uint32_t version);
    uint32_t _transactionGetLockTime(_transaction* _Nonnull instance);
    void _transactionSetLockTime(_transaction* _Nonnull instance, uint32_t lockTime);

    void _transactionSetInputs(_transaction* _Nonnull instance, const _input* const _Nonnull * inputs, size_t inputsCount);
    void _transactionGetInputs(_transaction* _Nonnull instance, _input* _Nonnull ** _Nonnull inputs, size_t* _Nonnull inputsCount);
    void _transactionSetOutputs(_transaction* _Nonnull instance, const _output* const _Nonnull * outputs, size_t outputsCount);
    void _transactionGetOutputs(_transaction* _Nonnull instance, _output* _Nonnull ** _Nonnull outputs, size_t* _Nonnull outputsCount);

#ifdef __cplusplus
}
#endif

#endif /* Transaction_hpp */

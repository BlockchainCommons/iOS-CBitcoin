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

    typedef struct _input _input;
    typedef struct _output _output;

    CBitcoinResult _transactionDecode(const uint8_t* data, size_t dataLength, bool isPretty, char** decoded, size_t* decodedLength);

    typedef struct _transaction _transaction;
    _transaction* _Nonnull _transactionNew();
    _transaction* _Nonnull _transactionCopy(_transaction* _Nonnull instance);
    CBitcoinResult _transactionDeserialize(const uint8_t* data, size_t dataLength, _transaction** instance);
    void _transactionSerialize(_transaction* _Nonnull instance, uint8_t** data, size_t* dataLength);
    bool _transactionIsValid(_transaction* _Nonnull instance);
    bool _transactionIsCoinbase(_transaction* _Nonnull instance);
    bool _transactionIsOversizedCoinbase(_transaction* _Nonnull instance);
    bool _transactionIsNullNonCoinbase(_transaction* _Nonnull instance);
    uint32_t _transactionGetVersion(_transaction* _Nonnull instance);
    void _transactionSetVersion(_transaction* _Nonnull instance, uint32_t version);
    uint32_t _transactionGetLockTime(_transaction* _Nonnull instance);
    void _transactionSetLockTime(_transaction* _Nonnull instance, uint32_t lockTime);
    void _transactionSetInputs(_transaction* _Nonnull instance, const _input* const _Nonnull * inputs, size_t inputsCount);
    void _transactionGetInputs(_transaction* _Nonnull instance, _input* _Nonnull ** _Nonnull inputs, size_t* _Nonnull inputsCount);
    void _transactionSetOutputs(_transaction* _Nonnull instance, const _output* const _Nonnull * outputs, size_t outputsCount);
    void _transactionGetOutputs(_transaction* _Nonnull instance, _output* _Nonnull ** _Nonnull outputs, size_t* _Nonnull outputsCount);
    bool _transactionIsFinal(_transaction* _Nonnull instance, size_t blockHeight, uint32_t blockTime);
    bool _transactionIsLocked(_transaction* _Nonnull instance, size_t blockHeight, uint32_t medianTimePast);
    bool _transactionIsLockTimeConflict(_transaction* _Nonnull instance);
    size_t _transactionSerializedSize(_transaction* _Nonnull instance);
    void _transactionHash(_transaction* _Nonnull instance, uint8_t** hash, size_t* hashLength);
    uint64_t _transactionTotalInputValue(_transaction* _Nonnull instance);
    uint64_t _transactionTotalOutputValue(_transaction* _Nonnull instance);
    bool _transactionIsOverspent(_transaction* _Nonnull instance);
    size_t _transactionSignatureOperationsCount(_transaction* _Nonnull instance, bool bip16, bool bip141);
    bool _transactionIsMissingPreviousOutputs(_transaction* _Nonnull instance);
    bool _transactionIsConfirmedDoubleSpend(_transaction* _Nonnull instance);
    bool _transactionIsDusty(_transaction* _Nonnull instance, uint64_t minimumOutputValue);
    bool _transactionIsMature(_transaction* _Nonnull instance, size_t height);
    bool _transactionIsInternalDoubleSpend(_transaction* _Nonnull instance);

#ifdef __cplusplus
}
#endif

#endif /* Transaction_hpp */

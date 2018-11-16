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
#include "Input.hpp"
#include "Output.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    CBitcoinResult _transactionDecode(const uint8_t* data, size_t dataLength, bool isPretty, char** decoded, size_t* decodedLength);

    typedef struct _transaction _transaction;
    _transaction* _Nonnull _transactionNew();
    _transaction* _Nonnull _transactionCopy(_transaction* _Nonnull instance);
    CBitcoinResult _transactionFromData(const uint8_t* data, size_t dataLength, _transaction** instance);
    void _transactionToData(_transaction* _Nonnull instance, uint8_t** data, size_t* dataLength);
    bool _transactionIsValid(_transaction* _Nonnull instance);
    bool _transactionIsCoinbase(_transaction* _Nonnull instance);
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

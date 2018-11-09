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
    void _outputPointDelete(_outputPoint* _Nonnull op);
    uint32_t _outputPointGetIndex(_outputPoint* _Nonnull op);
    void _outputPointSetIndex(_outputPoint* _Nonnull op, uint32_t index);
    void _outputPointGetHash(_outputPoint* _Nonnull op, uint8_t** hash, size_t* hashLength);
    void _outputPointSetHash(_outputPoint* _Nonnull op, const uint8_t* hash);

    typedef struct _input _input;
    _input* _Nonnull _inputNew();
    void _inputDelete(_input* _Nonnull i);
    _outputPoint* _Nonnull _inputGetPreviousOutput(_input* _Nonnull i);
    void _inputSetPreviousOutput(_input* _Nonnull i, _outputPoint* _Nonnull op);
    uint32_t _inputGetSequence(_input* _Nonnull i);
    void _inputSetSequence(_input* _Nonnull i, uint32_t sequence);

    typedef struct _output _output;
    _output* _Nonnull _outputNew();
    void _outputDelete(_output* _Nonnull o);
    CBitcoinResult _outputSetPaymentAddress(_output* _Nonnull o, const char* address);
    uint64_t _outputGetValue(_output* _Nonnull o);
    void _outputSetValue(_output* _Nonnull o, uint64_t value);
    void _outputGetScript(_output* _Nonnull o, char** decoded, size_t* decodedLength);

#ifdef __cplusplus
}
#endif

#endif /* Transaction_hpp */

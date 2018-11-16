//
//  Script.hpp
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

#ifndef Script_hpp
#define Script_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct _operation _operation;
    typedef struct _transaction _transaction;

    void _scriptDecode(const uint8_t* data, size_t dataLength, char** decoded, size_t* decodedLength);
    CBitcoinResult _scriptEncode(const char* script, uint8_t** encoded, size_t* encodedLength);
    CBitcoinResult _scriptToAddress(const char* script, uint8_t version, char** paymentAddress, size_t* paymentAddressLength);

    typedef struct _script _script;
    _script* _Nonnull _scriptNew();
    _script* _Nonnull _scriptCopy(_script* _Nonnull instance);
    CBitcoinResult _scriptFromString(const char* string, _script** instance);
    CBitcoinResult _scriptFromData(const uint8_t* data, size_t dataLength, bool prefix, _script** instance);
    _script* _Nonnull _scriptFromOperations(const _operation* const _Nonnull * operations, size_t operationsCount);
    void _scriptToData(_script* _Nonnull instance, bool prefix, uint8_t** data, size_t* dataLength);
    bool _scriptIsValid(_script* _Nonnull instance);
    bool _scriptEqual(_script* _Nonnull instance1, _script* _Nonnull instance2);

    void _scriptGetOperations(_script* _Nonnull instance, _operation* _Nonnull ** _Nonnull operations, size_t* _Nonnull operationsCount);
    bool _scriptIsEmpty(_script* _Nonnull instance);
    void _scriptClear(_script* _Nonnull instance);

    void _scriptGetWitnessProgram(_script* _Nonnull instance, uint8_t** program, size_t* programLength);
    int _scriptGetVersion(_script* _Nonnull instance);
    int _scriptGetPattern(_script* _Nonnull instance);
    int _scriptGetInputPattern(_script* _Nonnull instance);
    int _scriptGetOutputPattern(_script* _Nonnull instance);

    void _scriptMakePayNullDataPattern(const uint8_t* data, size_t dataLength, _operation* _Nonnull ** _Nonnull operations, size_t* _Nonnull operationsCount);

    uint32_t _scriptVerify(_transaction* _Nonnull transactionInstance, uint32_t inputIndex, uint32_t rules, _script* _Nonnull prevoutScriptInstance, uint64_t value);
    
#ifdef __cplusplus
}
#endif

#endif /* Script_hpp */

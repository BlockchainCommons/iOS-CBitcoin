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

    void _scriptDecode(const uint8_t* _Nonnull data, size_t dataLength, char* _Nullable * _Nonnull decoded, size_t* _Nonnull decodedLength);
    CBitcoinResult _scriptEncode(const char* _Nonnull script, uint8_t* _Nullable * _Nonnull encoded, size_t* _Nonnull encodedLength);
    CBitcoinResult _scriptToAddress(const char* _Nonnull script, uint8_t version, char* _Nullable * _Nonnull paymentAddress, size_t* _Nonnull paymentAddressLength);

    typedef struct _script _script;
    _script* _Nonnull _scriptNew(void);
    _script* _Nonnull _scriptCopy(_script* _Nonnull instance);
    CBitcoinResult _scriptFromString(const char* _Nonnull string, _script* _Nullable * _Nonnull instance);
    CBitcoinResult _scriptDeserialize(const uint8_t* _Nonnull data, size_t dataLength, bool prefix, _script* _Nullable * _Nonnull instance);
    _script* _Nonnull _scriptFromOperations(const _operation* const _Nonnull * _Nonnull operations, size_t operationsCount);
    void _scriptSerialize(_script* _Nonnull instance, bool prefix, uint8_t* _Nullable * _Nonnull data, size_t* _Nonnull dataLength);
    size_t _scriptSerializedSize(_script* _Nonnull instance, bool prefix);
    bool _scriptIsValid(_script* _Nonnull instance);
    bool _scriptEqual(_script* _Nonnull instance1, _script* _Nonnull instance2);

    void _scriptGetOperations(_script* _Nonnull instance, _operation* _Nonnull * _Nullable * _Nonnull operations, size_t* _Nonnull operationsCount);
    bool _scriptIsEmpty(_script* _Nonnull instance);
    void _scriptClear(_script* _Nonnull instance);

    void _scriptGetWitnessProgram(_script* _Nonnull instance, uint8_t* _Nullable * _Nonnull program, size_t* _Nonnull programLength);
    int _scriptGetVersion(_script* _Nonnull instance);
    int _scriptGetPattern(_script* _Nonnull instance);
    int _scriptGetInputPattern(_script* _Nonnull instance);
    int _scriptGetOutputPattern(_script* _Nonnull instance);

    void _scriptMakePayNullDataPattern(const uint8_t * _Nonnull data, size_t dataLength, _operation* _Nonnull * _Nullable * _Nonnull operations, size_t* _Nonnull operationsCount);
    void _scriptMakePayKeyHashPattern(const uint8_t* _Nonnull shortHash, _operation* _Nonnull * _Nullable * _Nonnull operations, size_t* _Nonnull operationsCount);
    void _scriptMakePayScriptHashPattern(const uint8_t* _Nonnull  shortHash, _operation* _Nonnull * _Nullable * _Nonnull operations, size_t* _Nonnull operationsCount);

    uint32_t _scriptVerify(_transaction* _Nonnull transactionInstance, uint32_t inputIndex, uint32_t rules, _script* _Nonnull prevoutScriptInstance, uint64_t value);

    void _generateSignatureHash(_transaction* _Nonnull transactionInstance, uint32_t inputIndex, _script* _Nonnull scriptInstance, uint8_t sigHashType, int32_t scriptVersion, uint64_t value, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull  hashLength);

    bool _checkSignature(const uint8_t* _Nonnull signature, uint8_t sigHashType, const uint8_t* _Nonnull publicKey, size_t publicKeyLength, _script* _Nonnull scriptInstance, _transaction* _Nonnull transactionInstance, uint32_t inputIndex, int32_t scriptVersion, uint64_t value);

    CBitcoinResult _createEndorsement(const uint8_t* _Nonnull ecPrivateKey, _script* _Nonnull scriptInstance, _transaction* _Nonnull transactionInstance, uint32_t inputIndex, uint8_t sigHashType, int32_t scriptVersion, uint64_t value, uint8_t* _Nullable * _Nonnull endorsement, size_t* _Nonnull endorsementLength);

#ifdef __cplusplus
}
#endif

#endif /* Script_hpp */

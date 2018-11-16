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

    void _scriptDecode(const uint8_t* data, size_t dataLength, char** decoded, size_t* decodedLength);
    CBitcoinResult _scriptEncode(const char* script, uint8_t** encoded, size_t* encodedLength);
    CBitcoinResult _scriptToAddress(const char* script, uint8_t version, char** paymentAddress, size_t* paymentAddressLength);

    typedef struct _script _script;
    _script* _Nonnull _scriptNew();
    _script* _Nonnull _scriptCopy(_script* _Nonnull instance);
    CBitcoinResult _scriptFromString(const char* string, _script** instance);
    CBitcoinResult _scriptFromData(const uint8_t* data, size_t dataLength, bool prefix, _script** instance);
    void _scriptToData(_script* _Nonnull instance, bool prefix, uint8_t** data, size_t* dataLength);
    bool _scriptIsValid(_script* _Nonnull instance);
    bool _scriptEqual(_script* _Nonnull instance1, _script* _Nonnull instance2);

#ifdef __cplusplus
}
#endif

#endif /* Script_hpp */

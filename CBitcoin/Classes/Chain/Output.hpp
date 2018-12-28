//
//  Output.hpp
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

#ifndef Output_hpp
#define Output_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"
#include "Script.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct _output _output;
    _output* _Nonnull _outputNew();
    _output* _Nonnull _outputCopy(_output* _Nonnull instance);
    CBitcoinResult _outputDeserialize(const uint8_t* data, size_t dataLength, _output** instance);
    void _outputSerialize(_output* _Nonnull instance, uint8_t** data, size_t* dataLength);
    bool _outputEqual(_output* _Nonnull instance1, _output* _Nonnull instance2);
    CBitcoinResult _outputSetPaymentAddress(_output* _Nonnull instance, const char* address);
    uint64_t _outputGetValue(_output* _Nonnull instance);
    void _outputSetValue(_output* _Nonnull instance, uint64_t value);
    void _outputGetScriptString(_output* _Nonnull instance, uint32_t activeRules, char** decoded, size_t* decodedLength);
    _script* _Nonnull _outputGetScript(_output* _Nonnull instance);
    void _outputSetScript(_output* _Nonnull instance, _script* _Nonnull scriptInstance);

#ifdef __cplusplus
}
#endif

#endif /* Output_hpp */

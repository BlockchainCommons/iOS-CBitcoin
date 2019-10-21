//
//  Input.hpp
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

#ifndef Input_hpp
#define Input_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"
#include "OutputPoint.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct _input _input;
    _input* _Nonnull _inputNew(void);
    _input* _Nonnull _inputCopy(_input* _Nonnull instance);
    CBitcoinResult _inputDeserialize(const uint8_t* _Nonnull data, size_t dataLength, _input* _Nullable * _Nonnull instance);
    void _inputSerialize(_input* _Nonnull instance, uint8_t* _Nullable * _Nonnull data, size_t* _Nonnull dataLength);
    bool _inputEqual(_input* _Nonnull instance1, _input* _Nonnull instance2);
    _outputPoint* _Nonnull _inputGetPreviousOutput(_input* _Nonnull const instance);
    void _inputSetPreviousOutput(_input* _Nonnull instance, _outputPoint* _Nonnull outputPointInstance);
    _script* _Nonnull _inputGetScript(_input* _Nonnull instance);
    void _inputSetScript(_input* _Nonnull instance, _script* _Nonnull scriptInstance);
    uint32_t _inputGetSequence(_input* _Nonnull instance);
    void _inputSetSequence(_input* _Nonnull instance, uint32_t sequence);
    void _inputGetScriptString(_input* _Nonnull instance, uint32_t activeRules, char* _Nullable * _Nonnull decoded, size_t* _Nonnull decodedLength);
    bool _inputIsValid(_input* _Nonnull instance);

#ifdef __cplusplus
}
#endif

#endif /* Input_hpp */

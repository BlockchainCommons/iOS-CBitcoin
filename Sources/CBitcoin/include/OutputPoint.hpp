//
//  OutputPoint.hpp
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

#ifndef OutputPoint_hpp
#define OutputPoint_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct _script _script;

    typedef struct _outputPoint _outputPoint;
    _outputPoint* _Nonnull _outputPointNew(void);
    _outputPoint* _Nonnull _outputPointCopy(_outputPoint* _Nonnull instance);
    CBitcoinResult _outputPointDeserialize(const uint8_t* _Nonnull data, size_t dataLength, _outputPoint* _Nullable * _Nonnull instance);
    void _outputPointSerialize(_outputPoint* _Nonnull instance, uint8_t* _Nullable * _Nonnull data, size_t* _Nonnull dataLength);
    bool _outputPointIsValid(_outputPoint* _Nonnull instance);
    bool _outputPointIsNull(_outputPoint* _Nonnull instance);
    bool _outputPointEqual(_outputPoint* _Nonnull instance1, _outputPoint* _Nonnull instance2);
    uint32_t _outputPointGetIndex(_outputPoint* _Nonnull instance);
    void _outputPointSetIndex(_outputPoint* _Nonnull instance, uint32_t index);
    void _outputPointGetHash(_outputPoint* _Nonnull instance, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength);
    void _outputPointSetHash(_outputPoint* _Nonnull instance, const uint8_t* _Nonnull hash);

#ifdef __cplusplus
}
#endif

#endif /* OutputPoint_hpp */

//
//  Operation.hpp
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

#ifndef Operation_hpp
#define Operation_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct _operation _operation;

    _operation* _Nonnull _operationNew(void);
    _operation* _Nonnull _operationFromOpcode(uint8_t opcode);
    CBitcoinResult _operationFromData(const uint8_t* data, size_t dataLength, bool isMinimal, _operation** instance);

    CBitcoinResult _operationDeserialize(const uint8_t* data, size_t dataLength, _operation** instance);
    void _operationSerialize(_operation* _Nonnull instance, uint8_t** data, size_t* dataLength);

    CBitcoinResult _operationFromString(const char* string, _operation** instance);
    void _operationToString(_operation* _Nonnull instance, uint32_t activeRules, char** string, size_t* stringLength);

    bool _operationIsValid(_operation* _Nonnull instance);
    bool _operationEqual(_operation* _Nonnull instance1, _operation* _Nonnull instance2);

    uint8_t _operationGetOpcode(_operation* _Nonnull instance);
    void _operationGetData(_operation* _Nonnull instance, uint8_t** data, size_t *dataLength);

#ifdef __cplusplus
}
#endif

#endif /* Operation_hpp */

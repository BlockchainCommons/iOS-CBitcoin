//
//  Opcode.hpp
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

#ifndef Opcode_hpp
#define Opcode_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    void _opcodeToString(uint8_t opcode, uint32_t activeRules, char** string, size_t* stringLength);
    CBitcoinResult _opcodeFromString(const char* string, uint8_t* opcode);
    void _opcodeToHexadecimal(uint8_t opcode, char** string, size_t* stringLength);
    CBitcoinResult _opcodeFromHexadecimal(const char* string, uint8_t* opcode);

#ifdef __cplusplus
}
#endif

#endif /* Opcode_hpp */

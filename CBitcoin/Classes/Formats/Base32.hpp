//
//  Base32.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/27/18.
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

#ifndef Base32_hpp
#define Base32_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    void _encodeBase32(const char* prefix, const uint8_t* payload, size_t payloadLength, char** string, size_t* stringLength);
    CBitcoinResult _decodeBase32(const char* string, char** prefix, size_t* prefixLength, uint8_t** payload, size_t* payloadLength);

#ifdef __cplusplus
}
#endif

#endif /* Base32_hpp */

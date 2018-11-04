//
//  Base16.hpp
//  Bitcoin
//
//  Created by Wolf McNally on 10/24/18.
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

#ifndef Base16_hpp
#define Base16_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    void _base16Encode(const uint8_t* data, size_t length, char** string, size_t* stringLength);
    CBitcoinResult _base16Decode(const char* string, uint8_t** data, size_t* dataLength);
    void _bitcoinHashEncode(const uint8_t* data, char** string, size_t* stringLength);
    CBitcoinResult _bitcoinHashDecode(const char* string, uint8_t** data, size_t* dataLength);

#ifdef __cplusplus
}
#endif

#endif /* Base16_hpp */

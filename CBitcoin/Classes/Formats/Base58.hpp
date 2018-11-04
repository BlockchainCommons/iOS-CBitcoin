//
//  Base58.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/22/18.
//  Copyright © 2018 Arciem LLC. All rights reserved.
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

#ifndef Base58_hpp
#define Base58_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    bool _isBase58Char(char c);
    bool _isBase58String(const char* string);
    void _base58Encode(const uint8_t* data, size_t length, char** string, size_t* stringLength);
    CBitcoinResult _base58Decode(const char* string, uint8_t** data, size_t* dataLength);
    void _base58CheckEncode(const uint8_t* data, size_t length, uint8_t version, char** string, size_t* stringLength);
    CBitcoinResult _base58CheckDecode(const char* string, uint8_t** data, size_t* dataLength, uint8_t* version);

#ifdef __cplusplus
}
#endif

#endif /* Base58_hpp */

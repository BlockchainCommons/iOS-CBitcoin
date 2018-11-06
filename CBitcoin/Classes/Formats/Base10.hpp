//
//  Base10.hpp
//  CBitcoin
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

#ifndef Base10_hpp
#define Base10_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    uint8_t _btcDecimalPlaces();
    uint8_t _mbtcDecimalPlaces();
    uint8_t _ubtcDecimalPlaces();

    void _base10Encode(uint64_t amount, char** string, size_t* stringLength, uint8_t decimalPlaces);
    CBitcoinResult _base10Decode(const char* string, uint64_t* amount, size_t decimalPlaces, bool strict);

#ifdef __cplusplus
}
#endif

#endif /* Base10_hpp */

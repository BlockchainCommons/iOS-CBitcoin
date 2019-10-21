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

    void _encodeBase16(const uint8_t* _Nonnull data, size_t length, char* _Nullable * _Nonnull string, size_t* _Nonnull stringLength);
    CBitcoinResult _decodeBase16(const char* _Nonnull string, uint8_t* _Nullable * _Nonnull data, size_t* _Nonnull dataLength);
    void _encodeBitcoinHash(const uint8_t* _Nonnull data, char* _Nullable * _Nonnull string, size_t* _Nonnull stringLength);
    CBitcoinResult _decodeBitcoinHash(const char* _Nonnull string, uint8_t* _Nullable * _Nonnull data, size_t* _Nonnull dataLength);

#ifdef __cplusplus
}
#endif

#endif /* Base16_hpp */

//
//  WrappedData.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 11/6/18.
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

#ifndef WrappedData_hpp
#define WrappedData_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    void _wrapEncode(const uint8_t* _Nonnull data, size_t dataLength, uint8_t version, uint8_t* _Nullable * _Nonnull wrappedData, size_t* _Nonnull wrappedDataLength);
    CBitcoinResult _wrapDecode(const uint8_t* _Nonnull wrappedData, size_t wrappedDataLength, uint8_t* _Nonnull version, uint8_t* _Nullable * _Nonnull payload, size_t* _Nonnull payloadLength, uint32_t* _Nonnull checksum);

#ifdef __cplusplus
}
#endif

#endif /* WrappedData_hpp */

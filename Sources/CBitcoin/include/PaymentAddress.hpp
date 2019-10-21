//
//  PaymentAddress.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 11/5/18.
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

#ifndef PaymentAddress_hpp
#define PaymentAddress_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    void _addressEncode(const uint8_t* _Nonnull ripemd160, uint8_t version, char* _Nullable * _Nonnull paymentAddress, size_t* _Nonnull paymentAddressLength);
    CBitcoinResult _addressDecode(const char* _Nonnull address, uint8_t* _Nonnull version, uint8_t* _Nullable * _Nonnull payload, size_t* _Nonnull payloadLength, uint32_t* _Nonnull checksum);
    void _addressEmbed(const uint8_t* _Nonnull data, size_t dataLength, uint8_t version, char* _Nullable * _Nonnull paymentAddress, size_t* _Nonnull paymentAddressLength);
    CBitcoinResult _addressHash(const char* _Nonnull address, uint8_t* _Nullable * _Nonnull hash, size_t* _Nonnull hashLength);

#ifdef __cplusplus
}
#endif

#endif /* PaymentAddress_hpp */

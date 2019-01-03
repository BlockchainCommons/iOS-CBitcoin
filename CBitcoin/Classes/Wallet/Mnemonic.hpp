//
//  Mnemonic.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/29/18.
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

#ifndef Mnemonic_hpp
#define Mnemonic_hpp

#include <stdlib.h>
#include "CBitcoinResult.hpp"

#ifdef __cplusplus
extern "C" {
#endif

    size_t _mnemonicWordMultiple();
    size_t _mnemonicSeedMultiple();
    const void* _dictionaryForLanguage(const char* _Nonnull language);
    CBitcoinResult _mnemonicNew(const uint8_t* _Nonnull seed, size_t seedLength, const void* _Nonnull dictionary, char** mnemonic, size_t* mnemonicLength);
    CBitcoinResult _mnemonicToSeed(const char* _Nonnull mnemonic, const void* _Nonnull dictionary, const char* passphrase, uint8_t** seed, size_t* seedLength);

#ifdef __cplusplus
}
#endif

#endif /* Mnemonic_hpp */

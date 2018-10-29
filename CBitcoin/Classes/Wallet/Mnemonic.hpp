//
//  Mnemonic.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/29/18.
//

#ifndef Mnemonic_hpp
#define Mnemonic_hpp

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    size_t _mnemonicWordMultiple();
    size_t _mnemonicSeedMultiple();
    const void* _dictionaryForLanguage(const char* language);
    bool _mnemonicNew(const uint8_t* seed, size_t seedLength, const void* dictionary, char** mnemonic, size_t* mnemonicLength);

#ifdef __cplusplus
}
#endif

#endif /* Mnemonic_hpp */

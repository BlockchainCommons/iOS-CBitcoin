//
//  Base58.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/22/18.
//  Copyright © 2018 Arciem LLC. All rights reserved.
//

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

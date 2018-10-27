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

#ifdef __cplusplus
extern "C" {
#endif

    bool _isBase58Char(char c);
    bool _isBase58String(const char* string);
    void _encodeBase58(const uint8_t* data, size_t length, char** string, size_t* stringLength);
    void _decodeBase58(const char* string, uint8_t** data, size_t* dataLength);
    void _encodeBase58Check(const uint8_t* data, size_t length, uint8_t version, char** string, size_t* stringLength);

#ifdef __cplusplus
}
#endif

#endif /* Base58_hpp */

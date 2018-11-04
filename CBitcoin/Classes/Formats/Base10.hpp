//
//  Base10.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/24/18.
//

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

    void _encodeBase10(uint64_t amount, char** string, size_t* stringLength, uint8_t decimalPlaces);
    CBitcoinResult _decodeBase10(const char* string, uint64_t* amount, size_t decimalPlaces, bool strict);

#ifdef __cplusplus
}
#endif

#endif /* Base10_hpp */

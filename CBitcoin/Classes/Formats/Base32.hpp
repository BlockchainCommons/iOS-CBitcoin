//
//  Base32.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/27/18.
//

#ifndef Base32_hpp
#define Base32_hpp

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    void _encodeBase32(const char* prefix, const uint8_t* payload, size_t payloadLength, char** string, size_t* stringLength);
    void _decodeBase32(const char* string, char** prefix, size_t* prefixLength, uint8_t** payload, size_t* payloadLength);

#ifdef __cplusplus
}
#endif

#endif /* Base32_hpp */

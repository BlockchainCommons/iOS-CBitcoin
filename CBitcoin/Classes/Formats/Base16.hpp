//
//  Base16.hpp
//  Bitcoin
//
//  Created by Wolf McNally on 10/24/18.
//

#ifndef Base16_hpp
#define Base16_hpp

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    void _encodeBase16(const uint8_t* data, size_t length, char** string, size_t* stringLength);
    void _decodeBase16(const char* string, uint8_t** data, size_t* dataLength);
    void _encodeHash(const uint8_t* data, char** string, size_t* stringLength);
    void _decodeHash(const char* string, uint8_t** data, size_t* dataLength);

#ifdef __cplusplus
}
#endif

#endif /* Base16_hpp */

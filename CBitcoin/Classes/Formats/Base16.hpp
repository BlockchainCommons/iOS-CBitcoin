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

    void _base16Encode(const uint8_t* data, size_t length, char** string, size_t* stringLength);
    void _base16Decode(const char* string, uint8_t** data, size_t* dataLength);
    void _bitcoinHashEncode(const uint8_t* data, char** string, size_t* stringLength);
    void _bitcoinHashDecode(const char* string, uint8_t** data, size_t* dataLength);

#ifdef __cplusplus
}
#endif

#endif /* Base16_hpp */

//
//  Base64.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/25/18.
//

#ifndef Base64_hpp
#define Base64_hpp

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    void _base64Encode(const uint8_t* data, size_t length, char** string, size_t* stringLength);
    void _base64Decode(const char* string, uint8_t** data, size_t* dataLength);

#ifdef __cplusplus
}
#endif

#endif /* Base64_hpp */

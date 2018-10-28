//
//  Base85.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/25/18.
//

#ifndef Base85_hpp
#define Base85_hpp

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    void _base85Encode(const uint8_t* data, size_t length, char** string, size_t* stringLength);
    void _base85Decode(const char* string, uint8_t** data, size_t* dataLength);

#ifdef __cplusplus
}
#endif

#endif /* Base85_hpp */

//
//  Free.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/24/18.
//

#ifndef Free_hpp
#define Free_hpp

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    void _freeString(char* string);
    void _freeData(uint8_t* data);

#ifdef __cplusplus
}
#endif

#endif /* Free_hpp */

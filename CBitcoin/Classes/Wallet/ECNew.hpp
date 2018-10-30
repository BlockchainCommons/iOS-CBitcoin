//
//  ECNew.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/30/18.
//

#ifndef ECNew_hpp
#define ECNew_hpp

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    bool _ecNew(const uint8_t* seed, size_t seedLength, uint8_t** key, size_t* keyLength);

#ifdef __cplusplus
}
#endif

#endif /* ECNew_hpp */

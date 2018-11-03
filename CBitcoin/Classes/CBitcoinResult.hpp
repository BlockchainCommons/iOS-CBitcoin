//
//  CBitcoinResult.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/24/18.
//

#ifndef CBitcoinResult_hpp
#define CBitcoinResult_hpp

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef size_t CBitcoinResult;
    #define CBITCOIN_SUCCESS 0
    #define CBITCOIN_ERROR_INVALID_FORMAT 1
    #define CBITCOIN_ERROR_INVALID_DATA_SIZE 2
    #define CBITCOIN_ERROR_SEED_TOO_SMALL 3
    #define CBITCOIN_ERROR_INVALID_SEED_SIZE 4
    #define CBITCOIN_ERROR_INVALID_SEED 5
    #define CBITCOIN_ERROR_UNSUPPORTED_LANGUAGE 6
    #define CBITCOIN_ERROR_INVALID_VERSION 7
    #define CBITCOIN_ERROR_PRIVATE_KEY_REQUIRED 8
    #define CBITCOIN_ERROR_INVALID_KEY 9

#ifdef __cplusplus
}
#endif

#endif /* CBitcoinResult_hpp */

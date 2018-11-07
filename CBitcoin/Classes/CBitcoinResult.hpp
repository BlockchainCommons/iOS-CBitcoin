//
//  CBitcoinResult.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/24/18.
//
//  Copyright © 2018 Blockchain Commons.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

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
    #define CBITCOIN_ERROR_INVALID_ADDRESS 10
    #define CBITCOIN_ERROR_INVALID_CHECKSUM 11
    #define CBITCOIN_ERROR_INVALID_SCRIPT 12

#ifdef __cplusplus
}
#endif

#endif /* CBitcoinResult_hpp */

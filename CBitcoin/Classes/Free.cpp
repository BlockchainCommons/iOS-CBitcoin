//
//  Free.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/24/18.
//

#include "Free.hpp"

void _freeString(char* string) {
    free(string);
}

void _freeData(uint8_t* data) {
    free(data);
}

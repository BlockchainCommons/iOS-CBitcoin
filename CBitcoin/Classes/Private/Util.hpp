//
//  PrivateUtil.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/23/18.
//

#ifndef PrivateUtil_hpp
#define PrivateUtil_hpp

#include <bitcoin/bitcoin.hpp>

void _returnString(std::string s, char** string, size_t* stringLength);
void _returnData(const libbitcoin::data_chunk& chunk, uint8_t** data, size_t* dataLength);

libbitcoin::data_slice _toDataSlice(const uint8_t* data, uint32_t length);

#endif /* PrivateUtil_hpp */

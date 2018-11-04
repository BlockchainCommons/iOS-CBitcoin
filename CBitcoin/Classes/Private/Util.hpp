//
//  Util.hpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/23/18.
//

#ifndef Util_hpp
#define Util_hpp

#include <bitcoin/bitcoin.hpp>

void _sendString(std::string s, char** string, size_t* stringLength);
void _sendData(const libbitcoin::data_chunk& chunk, uint8_t** data, size_t* dataLength);

libbitcoin::data_slice _toDataSlice(const uint8_t* data, uint32_t length);

libbitcoin::data_chunk _toDataChunk(const uint8_t* data, uint32_t length);

//template <size_t Size>
//std::array<uint8_t, Size> _toArray(const uint8_t* data);

libbitcoin::hash_digest _toHashDigest(const uint8_t* data);

template<size_t SIZE>
void _sendData(const libbitcoin::byte_array<SIZE>& hash, uint8_t** data, size_t* dataLength) {
    *dataLength = hash.size();
    *data = static_cast<uint8_t*>(malloc(*dataLength));
    std::copy(hash.begin(), hash.end(), *data);
}

template<size_t SIZE>
void _toByteArray(libbitcoin::byte_array<SIZE>& array, const uint8_t* bytes) {
    auto p = bytes;
    for(typename libbitcoin::byte_array<SIZE>::iterator i = array.begin(); i != array.end();) {
        *i++ = *p++;
    }
}

#endif /* PrivateUtil_hpp */

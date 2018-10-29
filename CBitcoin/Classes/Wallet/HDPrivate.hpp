#ifndef hdPrivate_hpp
#define hdPrivate_hpp

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    size_t _minimumSeedSize();
    bool _hdNew(const uint8_t* seed, size_t seedLength, uint32_t version, char** key, size_t* keyLength);

#ifdef __cplusplus
}
#endif

#endif /* hdPrivate_hpp */

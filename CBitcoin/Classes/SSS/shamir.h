#ifndef shamir_h
#define shamir_h

#include <stddef.h>
#include <stdlib.h>


int _randombytes(void *buf, size_t n);
size_t _sss_message_length();
size_t _sss_share_length();
void _sss_create_shares(void *out, const uint8_t *data, uint8_t n, uint8_t k);
int _sss_combine_shares(uint8_t *data, const void *shares, uint8_t k);

#endif /* shamir_h */

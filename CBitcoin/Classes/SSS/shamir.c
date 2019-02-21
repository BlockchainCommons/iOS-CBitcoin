//
//  shamir.c
//  Bitcoin
//
//  Created by Wolf McNally on 2/20/19.
//

#include "shamir.h"
#include <randombytes.h>
#include <sss.h>
#include <tweetnacl.h>
#include <hazmat.h>

int _randombytes(void *buf, size_t n) {
    return randombytes(buf, n);
}

size_t _sss_message_length() {
    return sss_MLEN;
}

size_t _sss_share_length() {
    return sss_SHARE_LEN;
}

void _sss_create_shares(void *out, const uint8_t *data, uint8_t n, uint8_t k) {
    sss_create_shares(out, data, n, k);
}

int _sss_combine_shares(uint8_t *data, const void *shares, uint8_t k) {
    return sss_combine_shares(data, shares, k);
}

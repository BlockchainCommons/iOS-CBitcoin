//
//  shamir.c
//  CBitcoin
//
//  Created by Wolf McNally on 11/7/18.
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

#include "shamir.h"
#include <randombytes.h>
#include <sss.h>
#include <tweetnacl.h>
#include <hazmat.h>

int _randombytes(void * _Nonnull buf, size_t n) {
    return randombytes(buf, n);
}

size_t _sss_message_length() {
    return sss_MLEN;
}

size_t _sss_share_length() {
    return sss_SHARE_LEN;
}

void _sss_create_shares(void *out, const uint8_t * _Nonnull data, uint8_t n, uint8_t k) {
    sss_create_shares(out, data, n, k);
}

int _sss_combine_shares(uint8_t * _Nonnull data, const void * _Nonnull shares, uint8_t k) {
    return sss_combine_shares(data, shares, k);
}

int _sss_create_shares_varlen(uint8_t *out, const uint8_t *data, const size_t data_len, uint8_t n, uint8_t k) {
    return sss_create_shares_varlen(out, data, data_len, n, k);
}

int _sss_combine_shares_varlen(uint8_t *data, const uint8_t *shares, const size_t share_len, uint8_t k) {
    return sss_combine_shares_varlen(data, shares, share_len, k);
}


size_t _crypto_stream_keybytes() {
    return crypto_stream_KEYBYTES;
}

size_t _crypto_stream_noncebytes() {
    return crypto_stream_NONCEBYTES;
}

int _crypto_stream_xor(unsigned char* _Nonnull output, const unsigned char* _Nonnull input, size_t messageLength, const unsigned char* _Nonnull nonce, const unsigned char* _Nonnull key) {
    return crypto_stream_xor(output, input, messageLength, nonce, key);
}

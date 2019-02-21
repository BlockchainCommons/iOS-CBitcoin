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

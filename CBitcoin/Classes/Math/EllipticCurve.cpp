//
//  EllipticCurve.cpp
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

#include "EllipticCurve.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

CBitcoinResult _encodeSignature(const uint8_t* ecSignature, uint8_t** derSignature, size_t* derSignatureLength) {
    ec_signature ecSig;
    _toByteArray(ecSig, ecSignature);
    der_signature derSig;
    if(!encode_signature(derSig, ecSig)) {
        return CBITCOIN_ERROR_INVALID_SIGNATURE;
    }
    _sendData(derSig, derSignature, derSignatureLength);
    return CBITCOIN_SUCCESS;
}

CBitcoinResult _parseSignature(const uint8_t* derSignature, size_t derSignatureSize, bool isStrict, uint8_t** ecSignature, size_t* ecSignatureLength) {
    const der_signature derSig = _toDataChunk(derSignature, derSignatureSize);
    ec_signature ecSig;
    if(!parse_signature(ecSig, derSig, isStrict)) {
        return CBITCOIN_ERROR_INVALID_SIGNATURE;
    }
    _sendData(ecSig, ecSignature, ecSignatureLength);
    return CBITCOIN_SUCCESS;
}

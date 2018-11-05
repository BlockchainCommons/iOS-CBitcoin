//
//  Message.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 11/5/18.
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

#include "Message.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

void _messageSign(const uint8_t* message, size_t messageLength, const char* wifKey, char** signature, size_t* signatureLength) {
    const auto messageSlice = _toDataSlice(message, messageLength);
    const auto wifString = std::string(wifKey);
    wallet::ec_private secret(wifString);
    wallet::message_signature sign;
    wallet::sign_message(sign, messageSlice, secret);
    const auto signatureString = encode_base64(sign);
    _sendString(signatureString, signature, signatureLength);
}

//
//  Script.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 11/7/18.
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

#include "Script.hpp"
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"

using namespace libbitcoin;

void _scriptDecode(const uint8_t* data, size_t dataLength, char** decoded, size_t* decodedLength) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    const auto script = chain::script(dataChunk, false);
    const auto decodedString = script.to_string(machine::rule_fork::all_rules);
    _sendString(decodedString, decoded, decodedLength);
}

CBitcoinResult _scriptEncode(const char* script, uint8_t** encoded, size_t* encodedLength) {
    const auto scriptString = std::string(script);
    chain::script s;
    if(!s.from_string(scriptString)) {
        return CBITCOIN_ERROR_INVALID_SCRIPT;
    }
    const auto encodedData = s.to_data(false);
    _sendData(encodedData, encoded, encodedLength);
    return CBITCOIN_SUCCESS;
}

//
//  Transaction.cpp
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

#include "Transaction.hpp"
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <bitcoin/bitcoin.hpp>
#include "Util.hpp"
#include <sstream>

using namespace libbitcoin;

CBitcoinResult _transactionDecode(const uint8_t* data, size_t dataLength, bool isPretty, char** decoded, size_t* decodedLength) {
    const auto dataChunk = _toDataChunk(data, dataLength);
    chain::transaction tx;
    if(!tx.from_data(dataChunk)) {
        return CBITCOIN_ERROR_INVALID_TRANSACTION;
    }
    const auto ptree = property_tree(tx, true);
    std::stringstream o;
    boost::property_tree::write_json(o, ptree, isPretty);
    _sendString(o.str(), decoded, decodedLength);
    return CBITCOIN_SUCCESS;
}

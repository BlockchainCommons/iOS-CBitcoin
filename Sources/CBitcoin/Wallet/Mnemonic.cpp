//
//  Mnemonic.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/29/18.
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

#include "Mnemonic.hpp"
#include <bitcoin/bitcoin.hpp>
#include <boost/algorithm/string.hpp>
#include "Util.hpp"

using namespace libbitcoin;

size_t _mnemonicWordMultiple(void) {
    return wallet::mnemonic_word_multiple;
}

size_t _mnemonicSeedMultiple(void) {
    return wallet::mnemonic_seed_multiple;
}

const wallet::dictionary* _dictionaryForLanguage(std::string languageString) {
    if(languageString == "en") {
        return &wallet::language::en;
    } else if(languageString == "es") {
        return &wallet::language::es;
    } else if(languageString == "ja") {
        return &wallet::language::ja;
    } else if(languageString == "it") {
        return &wallet::language::it;
    } else if(languageString == "fr") {
        return &wallet::language::fr;
    } else if(languageString == "cs") {
        return &wallet::language::cs;
    } else if(languageString == "ru") {
        return &wallet::language::ru;
    } else if(languageString == "uk") {
        return &wallet::language::uk;
    } else if(languageString == "zh_Hans") {
        return &wallet::language::zh_Hans;
    } else if(languageString == "zh_Hant") {
        return &wallet::language::zh_Hant;
    } else {
        return NULL;
    }
}

const void* _Nullable _dictionaryForLanguage(const char* _Nonnull language) {
    const wallet::dictionary* dict = _dictionaryForLanguage(std::string(language));
    return (void*)dict;
}

CBitcoinResult _wordlistForLanguage(const char* _Nonnull language, char* _Nullable * _Nonnull wordList, size_t* _Nonnull wordListLength) {
    const wallet::dictionary* dict = _dictionaryForLanguage(std::string(language));
    if(dict == NULL) {
        return CBITCOIN_ERROR_UNSUPPORTED_LANGUAGE;
    }
    auto words = std::vector<std::string>();
    std::transform(dict->begin(), dict->end(), std::back_inserter(words), [](const char* c) -> std::string { return std::string(c); });
    std::string joinedWords = boost::algorithm::join(words, " ");
    _sendString(joinedWords, wordList, wordListLength);
    return CBITCOIN_SUCCESS;
}

CBitcoinResult _mnemonicNew(const uint8_t* _Nonnull seed, size_t seedLength, const void* _Nonnull dictionary, char* _Nullable * _Nonnull mnemonic, size_t* _Nonnull mnemonicLength) {
    const auto entropy = _toDataChunk(seed, seedLength);
    if(entropy.size() % wallet::mnemonic_seed_multiple != 0) {
        return CBITCOIN_ERROR_INVALID_SEED_SIZE;
    }
    const auto dict = *(const wallet::dictionary*)dictionary;
    const auto words = wallet::create_mnemonic(entropy, dict);
    const auto mnemonicString = join(words);
    _sendString(mnemonicString, mnemonic, mnemonicLength);
    return CBITCOIN_SUCCESS;
}

/// Passphrase must already be normalized
long_hash _decode_mnemonic(const wallet::word_list& mnemonic,
                           const std::string& passphrase)
{
    const std::string prefix = "mnemonic";
    auto hmac_iterations = 2048;

    const auto sentence = join(mnemonic);
    const auto salt = prefix + passphrase;
    return pkcs5_pbkdf2_hmac_sha512(to_chunk(sentence), to_chunk(salt), hmac_iterations);
}

/// Passphrase must already be normalized
CBitcoinResult _mnemonicToSeed(const char* _Nonnull mnemonic, const void* _Nonnull dictionary, const char* _Nullable passphrase, uint8_t* _Nullable * _Nonnull seed, size_t* _Nonnull seedLength) {
    const auto mnemonicString = std::string(mnemonic);
    std::vector<std::string> words;
    boost::split(words, mnemonicString, [](char c){return c == ' ';});
    if(words.size() % wallet::mnemonic_word_multiple != 0) {
        return CBITCOIN_ERROR_INVALID_FORMAT;
    }
    const auto dict = *(const wallet::dictionary*)dictionary;
    if(!wallet::validate_mnemonic(words, dict)) {
        return CBITCOIN_ERROR_INVALID_FORMAT;
    }
    if(passphrase == NULL) {
        auto seedArray = wallet::decode_mnemonic(words);
        _sendData(seedArray, seed, seedLength);
    } else {
        auto passphraseString = std::string(passphrase);
        auto seedArray = _decode_mnemonic(words, passphraseString);
        _sendData(seedArray, seed, seedLength);
    }
    return CBITCOIN_SUCCESS;
}

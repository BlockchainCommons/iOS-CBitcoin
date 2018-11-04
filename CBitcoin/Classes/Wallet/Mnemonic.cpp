//
//  Mnemonic.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/29/18.
//

#include "Mnemonic.hpp"
#include <bitcoin/bitcoin.hpp>
#include <boost/algorithm/string.hpp>
#include "Util.hpp"

using namespace libbitcoin;

size_t _mnemonicWordMultiple() {
    return wallet::mnemonic_word_multiple;
}

size_t _mnemonicSeedMultiple() {
    return wallet::mnemonic_seed_multiple;
}

const void* _dictionaryForLanguage(const char* language) {
    auto languageString = std::string(language);
    const wallet::dictionary* dict;
    if(languageString == "en") {
        dict = &wallet::language::en;
    } else if(languageString == "es") {
        dict = &wallet::language::es;
    } else if(languageString == "ja") {
        dict = &wallet::language::ja;
    } else if(languageString == "it") {
        dict = &wallet::language::it;
    } else if(languageString == "fr") {
        dict = &wallet::language::fr;
    } else if(languageString == "cs") {
        dict = &wallet::language::cs;
    } else if(languageString == "ru") {
        dict = &wallet::language::ru;
    } else if(languageString == "uk") {
        dict = &wallet::language::uk;
    } else if(languageString == "zh_Hans") {
        dict = &wallet::language::zh_Hans;
    } else if(languageString == "zh_Hant") {
        dict = &wallet::language::zh_Hant;
    } else {
        return NULL;
    }
    return (void*)dict;
}

bool _mnemonicNew(const uint8_t* seed, size_t seedLength, const void* dictionary, char** mnemonic, size_t* mnemonicLength) {
    const auto entropy = _toDataChunk(seed, seedLength);
    if(entropy.size() % wallet::mnemonic_seed_multiple != 0) {
        return false;
    }
    const auto dict = *(const wallet::dictionary*)dictionary;
    const auto words = wallet::create_mnemonic(entropy, dict);
    const auto mnemonicString = join(words);
    _sendString(mnemonicString, mnemonic, mnemonicLength);
    return true;
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
bool _mnemonicToSeed(const char* mnemonic, const void* dictionary, const char* passphrase, uint8_t** seed, size_t* seedLength) {
    const auto mnemonicString = std::string(mnemonic);
    std::vector<std::string> words;
    boost::split(words, mnemonicString, [](char c){return c == ' ';});
    if(words.size() % wallet::mnemonic_word_multiple != 0) {
        seed = NULL;
        return false;
    }
    const auto dict = *(const wallet::dictionary*)dictionary;
    if(!wallet::validate_mnemonic(words, dict)) {
        seed = NULL;
        return false;
    }
    if(passphrase == NULL) {
        passphrase = "";
    }
    auto passphraseString = std::string(passphrase);
    if(passphraseString.empty()) {
        auto seedArray = wallet::decode_mnemonic(words);
        _sendData(seedArray, seed, seedLength);
    } else {
        auto seedArray = _decode_mnemonic(words, passphraseString);
        _sendData(seedArray, seed, seedLength);
    }
    return true;
}

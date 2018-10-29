//
//  Mnemonic.cpp
//  CBitcoin
//
//  Created by Wolf McNally on 10/29/18.
//

#include "Mnemonic.hpp"
#include <bitcoin/bitcoin.hpp>
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
    if(entropy.size() % _mnemonicSeedMultiple() != 0) {
        return false;
    }
    const auto dict = *(const wallet::dictionary*)dictionary;
    const auto words = wallet::create_mnemonic(entropy, dict);
    const auto mnemonicString = join(words);
    _returnString(mnemonicString, mnemonic, mnemonicLength);
    return true;
}

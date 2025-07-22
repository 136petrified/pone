/*   Created:  07-17-2025
 *   Modified: 07-21-2025
 */

#include "json_tokenizer.hpp"

#include <fstream>

namespace JSON {
Tokenizer::Tokenizer() {}

Tokenizer::Tokenizer(const std::string &file_name) : m_file_name{file_name} {}

bool Tokenizer::isAlnum(std::string &s) {
    for (char &c : s) {
        if (!std::isalnum(c)) return false;
    }

    return true;
}

bool Tokenizer::isAlpha(std::string &s) {
    for (char &c : s) {
        if (!std::isalpha(c)) return false;
    }

    return true;
}

bool Tokenizer::isDigit(std::string &s) {
    for (char &c : s) {
        if (!std::isdigit(c)) return false;
    }

    return true;
}

bool Tokenizer::isSymbol(std::string &s) {
    for (char &c : s) {
        if (!std::ispunct(c)) return false;
    }

    return true;
}

std::vector<std::string> Tokenizer::getTokens() const { return m_tokens; }

void

    Tokenizer::~Tokenizer() {}
}  // namespace JSON

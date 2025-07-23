/*   Created:  07-17-2025
 *   Modified: 07-21-2025
 */

#include "json_tokenizer.hpp"

#include <fstream>

#include "json_utils.hpp"

namespace JSON {
Tokenizer::Tokenizer() {}

Tokenizer::Tokenizer(const std::string &file_name) : m_file_name{file_name} {}

std::vector<std::string> Tokenizer::getTokens() const { return m_tokens; }

void Tokenizer::tokenize() {
    std::ifstream ifs{m_file_name};
    std::string buf;

    for (char c; ifs >> c;) {
    }
}

Tokenizer::~Tokenizer() {}
}  // namespace JSON

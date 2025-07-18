/*   Created:  07-17-2025
 *   Modified: 07-17-2025
 */

#include "json_tokenizer.hpp"

#include <fstream>

namespace JSON {
Tokenizer::Tokenizer() {}

Tokenizer::Tokenizer(const std::string &file_name) {
    std::ifstream ifs{file_name};
    std::string token;
    while (ifs >> token) m_tokens.push_back(token);
}

std::vector<std::string> Tokenizer::getTokens() const { return m_tokens; }

Tokenizer::~Tokenizer() {}
}  // namespace JSON

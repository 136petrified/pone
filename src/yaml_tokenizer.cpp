/*   Created:  07-23-2025
 *   Modified: 07-24-2025
 */

#include "yaml_tokenizer.hpp"

#include <fstream>

namespace YAML {
Tokenizer::Tokenizer() : m_buf{""} {}

Tokenizer::Tokenizer(const std::string &file_name)
    : m_file_name{file_name}, m_buf{""} {}

void Tokenizer::clearToken() {
    if (m_buf.empty()) return;
    m_tokens.push_back(m_buf);
    m_buf.clear();
}

std::vector<std::string> Tokenizer::getTokens() const { return m_tokens; }

void Tokenizer::next(std::ifstream &ifs) {
    ifs >> m_char;
    if (!ifs) throw EndOfIfstreamException();
}

void Tokenizer::scalar(std::ifstream &ifs) {
    while (isAlnum(m_char)) {
        m_buf += m_char;
        try {
            next(ifs);
        } catch (const EndOfIfstreamException &) {
            clearToken();
            return;
        }
    }
}

void Tokenizer::sym(std::ifstream &ifs) {}

void Tokenizer::tokenize() {
    std::ifstream ifs{m_file_name};
    try {
        next(ifs);  // Start with first token
    } catch (const EndOfIfstreamException &) {
        return;  // Means empty file
    }
}
}  // namespace YAML

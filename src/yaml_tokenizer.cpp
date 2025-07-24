/*   Created:  07-23-2025
 *   Modified: 07-24-2025
 */

#include "yaml_tokenizer.hpp"

#include <fstream>
#include <utility>

namespace YAML {
Tokenizer::Tokenizer() : m_buf{""}, m_endOfFile{false} {}

Tokenizer::Tokenizer(const std::string &file_name)
    : m_file_name{file_name}, m_buf{""}, m_endOfFile{false} {}

void Tokenizer::clearBuf() {
    if (m_buf.empty()) return;
    m_tokens.push_back(std::move(m_buf));
    m_buf.clear();
}

std::vector<std::string> Tokenizer::getTokens() const { return m_tokens; }

void Tokenizer::next(std::ifstream &ifs) {
    ifs >> m_char;
    if (ifs.eof()) {
        m_endOfFile = true;
        throw EndOfIfstreamException();
    }
}

void Tokenizer::scalar(std::ifstream &ifs) {
    while (isAlnum(m_char)) {
        m_buf += m_char;
        try {
            next(ifs);
        } catch (const EndOfIfstreamException &) {
            return;
        }
    }

    clearBuf();
}

void Tokenizer::sym(std::ifstream &ifs) {
    if (isSymbol(m_char)) {
        m_buf += m_char;
        try {
            next(ifs);
        } catch (const EndOfIfstreamException &) {
            return;
        }
    }

    clearBuf();
}

void Tokenizer::tokenize() {
    std::ifstream ifs{m_file_name};
    try {
        next(ifs);  // Start with first token
    } catch (const EndOfIfstreamException &) {
        return;  // Means empty file
    }

    while (!m_endOfFile) {
        scalar(ifs);
        sym(ifs);
    }
}
}  // namespace YAML

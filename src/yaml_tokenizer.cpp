/*   Created:  07-23-2025
 *   Modified: 07-24-2025
 */

#include "yaml_tokenizer.hpp"

#include <fstream>
#include <utility>

namespace YAML {

Token::Token(const TokenType &type, std::string &&data)
    : m_type{type}, m_data{std::move(data)} {}

std::string &&Token::getData() { return std::move(m_data); }

void Token::setData(const std::string &data) { m_data = data; }

Tokenizer::Tokenizer() : m_buf{""}, m_endOfFile{false} {}

Tokenizer::Tokenizer(const std::string &file_name)
    : m_file_name{file_name}, m_buf{""}, m_endOfFile{false} {}

void Tokenizer::clearBuf(const TokenType &tokenType) {
    if (m_buf.empty()) return;
    m_tokens.push_back(Token{tokenType, std::move(m_buf)});
    m_buf.clear();
}

std::vector<Token> Tokenizer::getTokens() const { return m_tokens; }

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

    clearBuf(TokenType::Scalar);
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

    clearBuf(TokenType::Symbol);
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

Tokenizer::~Tokenizer() {}
}  // namespace YAML

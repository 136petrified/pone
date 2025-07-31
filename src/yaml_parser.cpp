/*   Created:  07-23-2025
 *   Modified: 07-30-2025
 */

#include "yaml_parser.hpp"

#include <stdexcept>

#include "yaml_tokenizer.hpp"

namespace YAML {
Parser::Parser(const Tokenizer &tokenizer, const std::string &file_name)
    : m_tokenIndex{0},
      m_tokens{tokenizer.getTokens()},
      m_token{Token()},
      m_endOfFile{false},
      m_file_name{file_name} {}

void Parser::next() {
    try {
        m_token = m_tokens.at(m_tokenIndex++);
    } catch (const std::out_of_range &) {
        m_endOfFile = true;
    }
}

void Parser::comment() {
    while (m_token.m_type != TokenType::Newline) {
        next();  // Ignore every token until you get to a newline
    }
}

void Parser::parse() {
    next();
    while (!m_endOfFile) {
        scalar();
    }
}

void Parser::newline() { next(); }

void Parser::scalar() {
    if (m_token.m_type != TokenType::Scalar) return;
    key();  // Check if it is a key
}

void Parser::symbol() {
    if (!Token::isSymbol(m_token)) return;
    TokenType tokenType = m_token.m_type;
    if (tokenType == TokenType::Colon) {
        colon();
    }
}

}  // namespace YAML

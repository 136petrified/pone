/*   Created:  07-23-2025
 *   Modified: 08-02-2025
 */

#include "yaml_tokenizer.hpp"

#include <fstream>
#include <utility>

namespace YAML {

Token::Token() {}

Token::Token(const TokenType &type, std::string &&data)
    : m_type{type}, m_data{std::move(data)}, m_inQuotes{false} {}

std::string &&Token::getData() { return std::move(m_data); }

bool Token::inQuotes() const { return m_inQuotes; }

bool isSymbol(const Token &token) {
    TokenType tokenType = token.m_type;
    for (int i = 0; i < ALL_TOKEN_SYM_TYPES_SIZE; ++i) {
        if (tokenType == ALL_TOKEN_SYM_TYPES[i]) return true;
    }

    return false;
}

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

const char Tokenizer::lookahead(std::ifstream &ifs) const {
    // Looks ahead of the current character from ifstream
    int nextChar = ifs.peek();
    if (nextChar == std::char_traits<char>::eof()) {
        throw EndOfIfstreamException();
    }

    return static_cast<char>(nextChar);
}

void Tokenizer::next(std::ifstream &ifs) {
    ifs.get(m_char);
    if (ifs.eof()) {
        m_endOfFile = true;
        throw EndOfIfstreamException();
    }
}

void Tokenizer::scalar(std::ifstream &ifs) {
    if (!isAlnum(m_char)) return;
    while (isAlnum(m_char)) {
        m_buf += m_char;
        try {
            next(ifs);
        } catch (const EndOfIfstreamException &) {
            return;
        }
    }
}

void Tokenizer::sym(std::ifstream &ifs) {
    if (!isSymbol(m_char)) return;
    m_buf += m_char;

    switch (m_char) {
        case '\\':
            clearBuf(TokenType::Backslash);
            break;
        case ':':
            clearBuf(TokenType::Colon);
            break;
        case ',':
            clearBuf(TokenType::Comma);
            break;
        case '-':
            clearBuf(TokenType::Dash);
            break;
        case '"':
            clearBuf(TokenType::DoubleQuote);
            break;
        case '[':
            clearBuf(TokenType::LeftSquareBracket);
            break;
        case '#':
            clearBuf(TokenType::NumSign);
            break;
        case ']':
            clearBuf(TokenType::RightSquareBracket);
            break;
        case '\'':
            clearBuf(TokenType::SingleQuote);
            break;
        default:
            clearBuf(TokenType::Symbol);
            break;
    }

    try {
        next(ifs);
    } catch (const EndOfIfstreamException &) {
        return;
    }
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
        whitespace(ifs);
    }
}

void Tokenizer::whitespace(std::ifstream &ifs) {
    if (!isSpace(m_char)) return;
    m_buf += m_char;

    switch (m_char) {
        case '\n':
            clearBuf(TokenType::Newline);
            break;
        case ' ':
            clearBuf(TokenType::Space);
            break;
        case '\t':
            clearBuf(TokenType::Tab);
            break;
    }

    try {
        next(ifs);
    } catch (const EndOfIfstreamException &) {
        return;
    }
}

Tokenizer::~Tokenizer() {}
}  // namespace YAML

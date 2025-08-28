/*   Created:  07-23-2025
 *   Modified: 08-28-2025
 */

#include "yaml_tokenizer.hpp"

#include <fstream>
#include <utility>

namespace YAML {

Token::Token() {}

Token::Token(const Token::Type &type, std::string &&data)
    : m_type{type}, m_data{std::move(data)} {}

std::string &&Token::getData() {
    return std::move(m_data);
}  // NOTE: You can only do this once!

void Token::setData(const std::string &data) { m_data = data; }

Tokenizer::Tokenizer()
    : m_file_name{""}, m_ifs{""}, m_buf{""}, m_endOfFile{false} {}

Tokenizer::Tokenizer(const std::string &file_name)
    : m_file_name{file_name}, m_ifs{file_name}, m_buf{""}, m_endOfFile{false} {}

void Tokenizer::backslash() { tokenizeSpecialChar(Token::Type::Backslash); }

Token &Tokenizer::clearBuf(const Token::Type &tokenType) {
    Token token = Token{tokenType, std::move(m_buf)};
    m_tokens.push_back(token);
    m_buf.clear();
    return m_tokens.back();
}

void Tokenizer::colon() { tokenizeSpecialChar(Token::Type::Colon); }

void Tokenizer::comma() { tokenizeSpecialChar(Token::Type::Comma); }

void Tokenizer::comment() {
    while (m_char != '\n') {
        m_buf += m_char;  // Until the stream hits the newline, add to buffer
        try {
            next();
        } catch (const EndOfIfstreamException &) {
            clearBuf(Token::Type::Comment);
            return;
        }
    }

    clearBuf(Token::Type::Comment);
}

void Tokenizer::dash() { tokenizeSpecialChar(Token::Type::Dash); }

void Tokenizer::doubleQuote() { tokenizeSpecialChar(Token::Type::DoubleQuote); }

void Tokenizer::doubleQuotedKey() {
    while (m_char != '"') {
        if (m_char == '\\') {
            // Do not call backslash(), this will cause buf to clear
            // Backslash is not part of token data
            try {
                next();
            } catch (const EndOfIfstreamException &) {
                clearBuf(Token::Type::DoubleQuotedKey);
                return;
            }
        }

        m_buf += m_char;  // Assume that first quote is consumed
        try {
            next();
        } catch (const EndOfIfstreamException &) {
            clearBuf(Token::Type::DoubleQuotedKey);
            return;
        }
    }

    clearBuf(Token::Type::DoubleQuotedKey);
}

void Tokenizer::doubleQuotedValue() {
    while (m_char != '"') {
        if (m_char == '\\') {
            try {
                next();
            } catch (const EndOfIfstreamException &) {
                clearBuf(Token::Type::Backslash);
                return;
            }

            switch (m_char) {
                case '\\':
                    m_buf += '\\';
                    break;
                case '\"':
                    m_buf += '"';
                    break;
                case '\n':
                    m_buf += '\n';
                    break;
            }

            try {
                next();
            } catch (const EndOfIfstreamException &) {
                clearBuf(Token::Type::DoubleQuotedValue);
                return;
            }
        }
    }
}

std::vector<Token> Tokenizer::getTokens() const { return m_tokens; }

void Tokenizer::leftBrace() { tokenizeSpecialChar(Token::Type::LeftBrace); }

void Tokenizer::leftBracket() { tokenizeSpecialChar(Token::Type::LeftBracket); }

const char Tokenizer::lookahead() {
    // Looks ahead of the current character from ifstream
    int nextChar = m_ifs.peek();
    if (nextChar == std::char_traits<char>::eof()) {
        m_endOfFile = true;
        throw EndOfIfstreamException();
    }

    return static_cast<char>(nextChar);
}

void Tokenizer::rightBrace() { tokenizeSpecialChar(Token::Type::RightBrace); }

void Tokenizer::rightBracket() {
    tokenizeSpecialChar(Token::Type::RightBracket);
}

void Tokenizer::newline() { tokenizeSpecialChar(Token::Type::Newline); }

void Tokenizer::next() {
    m_ifs.get(m_char);
    if (m_ifs.eof()) {
        m_endOfFile = true;
        throw EndOfIfstreamException();
    }
}

void Tokenizer::numSign() { tokenizeSpecialChar(Token::Type::NumSign); }

void Tokenizer::otherSymbols() { tokenizeSpecialChar(Token::Type::Symbol); }

void Tokenizer::singleQuote() { tokenizeSpecialChar(Token::Type::SingleQuote); }

void Tokenizer::scalar() {
    if (!isAlnum(m_char)) return;
    while (isAlnum(m_char)) {
        m_buf += m_char;
        try {
            next();
        } catch (const EndOfIfstreamException &) {
            return;
        }
    }

    Token &tokenBuf = clearBuf(Token::Type::Key);

    while (isSpace(m_char)) {
        whitespace();
    }

    if (m_char != ':') {
        tokenBuf.m_type = Token::Type::Value;
    }
}

void Tokenizer::sym() {
    if (!isSymbol(m_char)) return;
    m_buf += m_char;

    switch (m_char) {
        case '\\':
            backslash();
            break;
        case ':':
            colon();
            break;
        case ',':
            comma();
            break;
        case '-':
            dash();
            break;
        case '"':
            doubleQuote();
            break;
        case '{':
            leftBrace();
            break;
        case '[':
            leftBracket();
            break;
        case '#':
            numSign();
            break;
        case '}':
            rightBrace();
            break;
        case ']':
            rightBracket();
            break;
        case '\'':
            singleQuote();
            break;
        default:
            otherSymbols();
            break;
    }

    try {
        next();
    } catch (const EndOfIfstreamException &) {
        return;
    }
}

void Tokenizer::tokenize() {
    try {
        next();  // Start with first token
    } catch (const EndOfIfstreamException &) {
        return;  // Means empty file
    }

    while (!m_endOfFile) {
        scalar();
        sym();
        whitespace();
    }
}

void Tokenizer::tokenizeSpecialChar(const Token::Type &tokenType) {
    try {
        next();
    } catch (const EndOfIfstreamException) {
        clearBuf(tokenType);
        return;
    }

    clearBuf(tokenType);
}

void Tokenizer::space() { tokenizeSpecialChar(Token::Type::Space); }

void Tokenizer::tab() { tokenizeSpecialChar(Token::Type::Tab); }

void Tokenizer::whitespace() {
    if (!isSpace(m_char)) return;
    m_buf += m_char;

    switch (m_char) {
        case '\n':
            newline();
            break;
        case ' ':
            space();
            break;
        case '\t':
            tab();
            break;
    }

    try {
        next();
    } catch (const EndOfIfstreamException &) {
        return;
    }
}

Tokenizer::~Tokenizer() {}
}  // namespace YAML

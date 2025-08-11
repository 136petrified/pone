/*   Created:  07-23-2025
 *   Modified: 08-11-2025
 */

#include "yaml_tokenizer.hpp"

#include <fstream>
#include <utility>

namespace YAML {

Token::Token() {}

Token::Token(const TokenType &type, std::string &&data)
    : m_type{type}, m_data{std::move(data)} {}

std::string &&Token::getData() {
    return std::move(m_data);
}  // NOTE: You can only do this once!

void Token::setData(const std::string &data) { m_data = data; }

Tokenizer::Tokenizer() : m_file_name{""}, m_buf{""}, m_endOfFile{false} {}

Tokenizer::Tokenizer(const std::string &file_name)
    : m_file_name{file_name}, m_buf{""}, m_endOfFile{false} {}

void Tokenizer::backslash(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::Backslash);
}

Token &Tokenizer::clearBuf(const TokenType &tokenType) {
    Token token = Token{tokenType, std::move(m_buf)};
    m_tokens.push_back(token);
    m_buf.clear();
    return m_tokens.back();
}

void Tokenizer::colon(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::Colon);
}

void Tokenizer::comma(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::Comma);
}

void Tokenizer::comment(std::ifstream &ifs) {
    while (m_char != '\n') {
        m_buf += m_char;  // Until the stream hits the newline, add to buffer
        try {
            next(ifs);
        } catch (const EndOfIfstreamException &) {
            clearBuf(TokenType::Comment);
            return;
        }
    }

    clearBuf(TokenType::Comment);
}

void Tokenizer::dash(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::Dash);
}

void Tokenizer::doubleQuote(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::DoubleQuote);
}

void Tokenizer::doubleQuotedKey(std::ifstream &ifs) {
    while (m_char != '"') {
        if (m_char == '\\') {
            // Do not call backslash(), this will cause buf to clear
            // Backslash is not part of token data
            try {
                next(ifs);
            } catch (const EndOfIfstreamException &) {
                clearBuf(TokenType::DoubleQuotedKey);
            }
        }

        m_buf += m_char;  // Assume that first quote is consumed
        try {
            next(ifs);
        } catch (const EndOfIfstreamException &) {
            clearBuf(TokenType::DoubleQuotedKey);
            return;
        }
    }
}

std::vector<Token> Tokenizer::getTokens() const { return m_tokens; }

void Tokenizer::leftBrace(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::LeftBrace);
}

void Tokenizer::leftBracket(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::LeftBracket);
}

const char Tokenizer::lookahead(std::ifstream &ifs) {
    // Looks ahead of the current character from ifstream
    int nextChar = ifs.peek();
    if (nextChar == std::char_traits<char>::eof()) {
        m_endOfFile = true;
        throw EndOfIfstreamException();
    }

    return static_cast<char>(nextChar);
}

void Tokenizer::rightBrace(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::RightBrace);
}

void Tokenizer::rightBracket(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::RightBracket);
}

void Tokenizer::newline(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::Newline);
}

void Tokenizer::next(std::ifstream &ifs) {
    ifs.get(m_char);
    if (ifs.eof()) {
        m_endOfFile = true;
        throw EndOfIfstreamException();
    }
}

void Tokenizer::numSign(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::NumSign);
}

void Tokenizer::otherSymbols(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::Symbol);
}

void Tokenizer::singleQuote(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::SingleQuote);
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

    Token &tokenBuf = clearBuf(TokenType::Key);

    while (isSpace(m_char)) {
        whitespace(ifs);
    }

    if (m_char != ':') {
        tokenBuf.m_type = TokenType::Value;
    }
}

void Tokenizer::sym(std::ifstream &ifs) {
    if (!isSymbol(m_char)) return;
    m_buf += m_char;

    switch (m_char) {
        case '\\':
            backslash(ifs);
            break;
        case ':':
            colon(ifs);
            break;
        case ',':
            comma(ifs);
            break;
        case '-':
            dash(ifs);
            break;
        case '"':
            doubleQuote(ifs);
            break;
        case '{':
            leftBrace(ifs);
            break;
        case '[':
            leftBracket(ifs);
            break;
        case '#':
            numSign(ifs);
            break;
        case '}':
            rightBrace(ifs);
            break;
        case ']':
            rightBracket(ifs);
            break;
        case '\'':
            singleQuote(ifs);
            break;
        default:
            otherSymbols(ifs);
            break;
    }

    try {
        next(ifs);
    } catch (const EndOfIfstreamException &) {
        return;
    }
}

void Tokenizer::toggleEscape() { m_isEscaped = !m_isEscaped; }

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

void Tokenizer::tokenizeSpecialChar(std::ifstream &ifs,
                                    const TokenType &tokenType) {
    try {
        next(ifs);
    } catch (const EndOfIfstreamException) {
        clearBuf(tokenType);
        return;
    }

    clearBuf(tokenType);
}

void Tokenizer::space(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::Space);
}

void Tokenizer::tab(std::ifstream &ifs) {
    tokenizeSpecialChar(ifs, TokenType::Tab);
}

void Tokenizer::whitespace(std::ifstream &ifs) {
    if (!isSpace(m_char)) return;
    m_buf += m_char;

    switch (m_char) {
        case '\n':
            newline(ifs);
            break;
        case ' ':
            space(ifs);
            break;
        case '\t':
            tab(ifs);
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

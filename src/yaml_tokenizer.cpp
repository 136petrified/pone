/*   Created:  07-23-2025
 *   Modified: 09-05-2025
 */

#include "yaml_tokenizer.hpp"

#include <utility>

namespace YAML {

Token::Token() {}

Token::~Token() {}

SingleToken::SingleToken() : m_class{Token::Class::Single} {}

SingleToken::SingleToken(const Token::Type &type)
    : m_class{Token::Class::Single}, m_data{""}, m_type{type} {}

SingleToken::SingleToken(const Token::Type &type, const std::string &data)
    : m_class{Token::Class::Single}, m_data{data}, m_type{type} {}

SingleToken::SingleToken(const Token::Type &type, std::string &&data)
    : m_class{Token::Class::Single}, m_data{std::move(data)}, m_type{type} {}

SingleToken::SingleToken(const SingleToken &other)
    : m_class{Token::Class::Single},
      m_data{other.m_data},
      m_type{other.m_type} {}

SingleToken &SingleToken::operator=(const SingleToken &other) {
    if (this != &other) {
        m_class = Token::Class::Single;  // might not be necessary
        m_data = other.m_data;
        m_type = other.m_type;
    }

    return *this;
}

std::string &&SingleToken::getData() { return std::move(m_data); }

std::unique_ptr<Token> SingleToken::clone() const {
    return std::make_unique<SingleToken>(*this);
}

void SingleToken::setData(const std::string &data) { m_data = data; }

Token::Class SingleToken::getClass() const { return m_class; }

Token::Type SingleToken::getType() const { return m_type; }

void SingleToken::setType(const Token::Type &type) { m_type = type; }

SingleToken::~SingleToken() {}

GroupToken::GroupToken() : m_class{Token::Class::Group} {}

GroupToken::GroupToken(const Token::Type &type)
    : m_class{Token::Class::Group}, m_type{type} {}

GroupToken::GroupToken(const GroupToken &other)
    : m_tokenGroupSize{other.m_tokenGroupSize} {
    for (auto &token : other.m_tokenGroup) {
        if (token != nullptr) {
            insertToTokenGroup(token->clone());
        }
    }
}

GroupToken &GroupToken::operator=(const GroupToken &other) {
    if (this != &other) {
        clearTokenGroup();
        for (auto &token : other.m_tokenGroup) {
            if (token != nullptr) {
                insertToTokenGroup(token->clone());
            }
        }
    }

    return *this;
}

void GroupToken::clearTokenGroup() {
    for (auto &token : m_tokenGroup) {
        if (token->getClass() == Token::Class::Group) {
            token->clearTokenGroup();
        }
    }
}

void GroupToken::insertToTokenGroup(std::unique_ptr<Token> &&token) {
    if (token != nullptr) {
        m_tokenGroup.push_back(std::move(token));
        ++m_tokenGroupSize;
    }
}

bool GroupToken::isTokenGroupEmpty() const { return m_tokenGroupSize <= 0; }

size_t GroupToken::sizeOfTokenGroup() const { return m_tokenGroupSize; }

std::unique_ptr<Token> GroupToken::clone() const {
    return std::make_unique<GroupToken>(*this);
}

GroupToken::~GroupToken() {}

Tokenizer::Tokenizer()
    : m_file_name{""}, m_ifs{""}, m_buf{""}, m_endOfFile{false} {}

Tokenizer::Tokenizer(const std::string &file_name)
    : m_file_name{file_name}, m_ifs{file_name}, m_buf{""}, m_endOfFile{false} {}

void Tokenizer::backslash() {}

void Tokenizer::clearBuf() {}

void Tokenizer::colon() {}

void Tokenizer::comma() { tokenizeSpecialChar(Token::Type::Comma); }

void Tokenizer::comment() {}

void Tokenizer::dash() {}

void Tokenizer::doubleQuote() {}

void Tokenizer::doubleQuotedKey() {}

void Tokenizer::doubleQuotedValue() {}

std::vector<std::unique_ptr<Token>> Tokenizer::getTokens() const {
    return std::vector<std::unique_ptr<Token>>();  // dummy value
}

void Tokenizer::leftBrace() {}

void Tokenizer::leftBracket() {}

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

void Tokenizer::numSign() {}

void Tokenizer::otherSymbols() {}

void Tokenizer::singleQuote() {}

void Tokenizer::scalar() {}

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
    }
}

void Tokenizer::space() {}

void Tokenizer::tab() {}

void Tokenizer::whitespace() {}

Tokenizer::~Tokenizer() {}
}  // namespace YAML

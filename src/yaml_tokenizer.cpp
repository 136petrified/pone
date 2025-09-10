/*   Created:  07-23-2025
 *   Modified: 09-10-2025
 */

#include "yaml_tokenizer.hpp"

#include <memory>
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

// Do not call clone()
// This will not copy members directly into the current object

GroupToken::GroupToken(const GroupToken &other)
    : m_tokenGroup{other.getTokenGroup()},
      m_tokenGroupSize{other.m_tokenGroupSize} {}

GroupToken &GroupToken::operator=(const GroupToken &other) {
    if (this != &other) {
        clearTokenGroup();
        m_tokenGroup = other.getTokenGroup();
    }

    return *this;
}

void GroupToken::clearTokenGroup() { m_tokenGroup.clear(); }

std::vector<std::unique_ptr<Token>> GroupToken::getTokenGroup() const {
    std::vector<std::unique_ptr<Token>> newTokenVector;

    for (const auto &token : m_tokenGroup) {
        if (token != nullptr) {
            newTokenVector.push_back(token->clone());
        }
    }

    return newTokenVector;
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
    // Make a new GroupToken
    // Do not call copy constructor
    // It does not use recursion directly
    GroupToken newGroupToken;

    newGroupToken.setType(m_type);

    for (const auto &token : m_tokenGroup) {
        if (token != nullptr) {
            // If this is a GroupToken, recursively add all subtokens
            newGroupToken.insertToTokenGroup(token->clone());
        }
    }

    return std::make_unique<GroupToken>(newGroupToken);
}

Token::Class GroupToken::getClass() const { return m_class; }

Token::Type GroupToken::getType() const { return m_type; }

void GroupToken::setType(const Token::Type &type) { m_type = type; }

GroupToken::~GroupToken() {}

Tokenizer::Tokenizer()
    : m_file_name{""},
      m_ifs{""},
      m_tokensSize{0},
      m_buf{""},
      m_endOfFile{false} {}

Tokenizer::Tokenizer(const std::string &file_name)
    : m_file_name{file_name},
      m_ifs{file_name},
      m_tokensSize{0},
      m_buf{""},
      m_endOfFile{false} {}

void Tokenizer::backslash() { createSingleToken(Token::Type::Backslash); }

void Tokenizer::backslash(GroupToken &gtok) {
    insertSingleTokenToGroupToken(gtok, Token::Type::Backslash);
}

void Tokenizer::clearBuf() { m_buf.clear(); }

void Tokenizer::colon() { createSingleToken(Token::Type::Colon); }

void Tokenizer::colon(GroupToken &gtok) {
    insertSingleTokenToGroupToken(gtok, Token::Type::Colon);
}

void Tokenizer::comma() { createSingleToken(Token::Type::Comma); }

void Tokenizer::comma(GroupToken &gtok) {
    insertSingleTokenToGroupToken(gtok, Token::Type::Comma);
}

void Tokenizer::comment() {}

std::unique_ptr<GroupToken> Tokenizer::createGroupToken(
    const Token::Type &tokenType) const {
    return std::make_unique<GroupToken>(GroupToken{tokenType});
}

std::unique_ptr<SingleToken> Tokenizer::createSingleToken(
    const Token::Type &tokenType) const {
    return std::make_unique<SingleToken>(SingleToken{tokenType});
}

std::unique_ptr<SingleToken> Tokenizer::createSingleToken(
    const Token::Type &tokenType, std::string &&data) const {
    return std::make_unique<SingleToken>(
        SingleToken{tokenType, std::move(data)});
}

void Tokenizer::dash() { createSingleToken(Token::Type::Dash); }

void Tokenizer::dash(GroupToken &gtok) {
    insertSingleTokenToGroupToken(gtok, Token::Type::Dash);
}

void Tokenizer::doubleQuote() { createSingleToken(Token::Type::DoubleQuote); }

void Tokenizer::doubleQuote(GroupToken &gtok) {
    insertSingleTokenToGroupToken(gtok, Token::Type::DoubleQuote);
}

std::vector<std::unique_ptr<Token>> Tokenizer::getTokens() const {
    /* Copy every single unique_ptr from m_tokens
     * and every GroupToken within it */

    std::vector<std::unique_ptr<Token>> newTokenVector;

    for (const auto &token : m_tokens) {
        if (token != nullptr) {
            newTokenVector.push_back(token->clone());
        }
    }

    return newTokenVector;
}

void Tokenizer::insertGroupTokenToGroupToken(GroupToken &to_gtok,
                                             const Token::Type &tokenType) {
    to_gtok.insertToTokenGroup(createGroupToken(tokenType));
}

void Tokenizer::insertGroupTokenToGroupToken(
    GroupToken &to_gtok, const std::unique_ptr<GroupToken> &gtokPtr) {
    to_gtok.insertToTokenGroup(gtokPtr->clone());
}

void Tokenizer::insertGroupTokenToGroupToken(
    GroupToken &to_gtok, std::unique_ptr<GroupToken> &&gtokPtr) {
    to_gtok.insertToTokenGroup(std::move(gtokPtr));
}

void Tokenizer::insertGroupTokenToTokens(const Token::Type &tokenType) {
    m_tokens.push_back(createGroupToken(tokenType));
}

void Tokenizer::insertGroupTokenToTokens(
    const std::unique_ptr<GroupToken> &gtokPtr) {
    m_tokens.push_back(gtokPtr->clone());
}

void Tokenizer::insertGroupTokenToTokens(
    std::unique_ptr<GroupToken> &&gtokPtr) {
    m_tokens.push_back(std::move(gtokPtr));
}

void Tokenizer::insertSingleTokenToGroupToken(GroupToken &to_gtok,
                                              const Token::Type &tokenType) {
    to_gtok.insertToTokenGroup(createSingleToken(tokenType));
}

void Tokenizer::insertSingleTokenToGroupToken(GroupToken &to_gtok,
                                              const Token::Type &tokenType,
                                              std::string &&data) {
    to_gtok.insertToTokenGroup(createSingleToken(tokenType, std::move(data)));
}

void Tokenizer::insertSingleTokenToGroupToken(
    GroupToken &to_gtok, const std::unique_ptr<SingleToken> &stokPtr) {
    to_gtok.insertToTokenGroup(stokPtr->clone());
}

void Tokenizer::insertSingleTokenToGroupToken(
    GroupToken &to_gtok, std::unique_ptr<SingleToken> &&stokPtr) {
    to_gtok.insertToTokenGroup(std::move(stokPtr));
}

void Tokenizer::insertSingleTokenToTokens(const Token::Type &tokenType) {
    m_tokens.push_back(createSingleToken(tokenType));
}

void Tokenizer::insertSingleTokenToTokens(const Token::Type &tokenType,
                                          std::string &&data) {
    m_tokens.push_back(createSingleToken(tokenType, std::move(data)));
}

void Tokenizer::insertSingleTokenToTokens(
    const std::unique_ptr<SingleToken> &stokPtr) {
    m_tokens.push_back(stokPtr->clone());
}

void Tokenizer::insertSingleTokenToTokens(
    std::unique_ptr<SingleToken> &&stokPtr) {
    m_tokens.push_back(std::move(stokPtr));
}

void Tokenizer::leftBrace() { createSingleToken(Token::Type::LeftBrace); }

void Tokenizer::leftBrace(GroupToken &gtok) {
    insertSingleTokenToGroupToken(gtok, Token::Type::LeftBrace);
}

void Tokenizer::leftBracket() { createSingleToken(Token::Type::LeftBracket); }

void Tokenizer::leftBracket(GroupToken &gtok) {
    insertSingleTokenToGroupToken(gtok, Token::Type::LeftBracket);
}

const char Tokenizer::lookahead() {
    // Looks ahead of the current character from ifstream
    int nextChar = m_ifs.peek();
    if (nextChar == std::char_traits<char>::eof()) {
        m_endOfFile = true;
        throw EndOfIfstreamException();
    }

    return static_cast<char>(nextChar);
}

void Tokenizer::mapping() {}

void Tokenizer::newline() { createSingleToken(Token::Type::Newline); }

void Tokenizer::next() {
    m_ifs.get(m_char);
    if (m_ifs.eof()) {
        m_endOfFile = true;
        throw EndOfIfstreamException();
    }
}

void Tokenizer::numSign() { createSingleToken(Token::Type::NumSign); }

void Tokenizer::numSign(GroupToken &gtok) {
    insertSingleTokenToGroupToken(gtok, Token::Type::NumSign);
}

void Tokenizer::otherSymbols() { createSingleToken(Token::Type::Symbol); }

void Tokenizer::otherSymbols(GroupToken &gtok) {
    insertSingleTokenToGroupToken(gtok, Token::Type::Symbol);
}

void Tokenizer::rightBrace() { createSingleToken(Token::Type::RightBrace); }

void Tokenizer::rightBrace(GroupToken &gtok) {
    insertSingleTokenToGroupToken(gtok, Token::Type::RightBrace);
}

void Tokenizer::rightBracket() { createSingleToken(Token::Type::RightBracket); }

void Tokenizer::rightBracket(GroupToken &gtok) {
    insertSingleTokenToGroupToken(gtok, Token::Type::RightBracket);
}

void Tokenizer::singleQuote() { createSingleToken(Token::Type::SingleQuote); }

void Tokenizer::singleQuote(GroupToken &gtok) {
    insertSingleTokenToGroupToken(gtok, Token::Type::SingleQuote);
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

void Tokenizer::sym(GroupToken &gtok) {
    if (!isSymbol(m_char)) return;
    m_buf += m_char;

    switch (m_char) {
        case '\\':
            backslash(gtok);
            break;
        case ':':
            colon(gtok);
            break;
        case ',':
            comma(gtok);
            break;
        case '-':
            dash(gtok);
            break;
        case '"':
            doubleQuote(gtok);
            break;
        case '{':
            leftBrace(gtok);
            break;
        case '[':
            leftBracket(gtok);
            break;
        case '#':
            numSign(gtok);
            break;
        case '}':
            rightBrace(gtok);
            break;
        case ']':
            rightBracket(gtok);
            break;
        case '\'':
            singleQuote(gtok);
            break;
        default:
            otherSymbols(gtok);
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

void Tokenizer::space() { createSingleToken(Token::Type::Space); }

void Tokenizer::space(GroupToken &gtok) {
    insertSingleTokenToGroupToken(gtok, Token::Type::Space);
}

void Tokenizer::tab() { createSingleToken(Token::Type::Tab); }

void Tokenizer::tab(GroupToken &gtok) {
    insertSingleTokenToGroupToken(gtok, Token::Type::Tab);
    // TODO: Implement token creation functions
}

void Tokenizer::whitespace() {
    while (isSpace(m_char)) {
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
}

void Tokenizer::whitespace(GroupToken &gtok) {
    while (isSpace(m_char)) {
        switch (m_char) {
            case '\n':
                newline(gtok);
                break;
            case ' ':
                space(gtok);
                break;
            case '\t':
                tab(gtok);
                break;
        }

        try {
            next();
        } catch (const EndOfIfstreamException) {
            return;
        }
    }
}

Tokenizer::~Tokenizer() {}
}  // namespace YAML

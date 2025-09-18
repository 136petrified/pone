/*   Created:  07-23-2025
 *   Modified: 09-17-2025
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

std::unique_ptr<Token> SingleToken::clone() const {
    try {
        return std::make_unique<SingleToken>(*this);
    } catch (const std::bad_alloc &e) {
        // TODO: Print error here
        return nullptr;
    }
}

const std::string &SingleToken::getData() const { return m_data; }

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

GroupToken::GroupToken(GroupToken &&other) noexcept {
    for (auto &token : other.m_tokenGroup) {
        // Each sub-GroupToken owns its own tokens
        // therefore, no copying is necessary
        m_tokenGroup.push_back(std::move(token));
    }

    m_tokenGroupSize = other.m_tokenGroupSize;
}

GroupToken &GroupToken::operator=(const GroupToken &other) {
    if (this != &other) {
        clearTokenGroup();
        m_tokenGroup = other.getTokenGroup();
    }

    return *this;
}

GroupToken &GroupToken::operator=(GroupToken &&other) noexcept {
    if (this != &other) {
        clearTokenGroup();
        for (auto &token : other.m_tokenGroup) {
            m_tokenGroup.push_back(std::move(token));
        }

        m_tokenGroupSize = other.m_tokenGroupSize;
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

    try {
        return std::make_unique<GroupToken>(newGroupToken);
    } catch (const std::bad_alloc &e) {
        // TODO: Print error here
        return nullptr;
    }
}

Token::Class GroupToken::getClass() const { return m_class; }

Token::Type GroupToken::getType() const { return m_type; }

void GroupToken::setType(const Token::Type &type) { m_type = type; }

GroupToken::~GroupToken() {}

Tokenizer::Tokenizer()
    : m_fileName{""},
      m_ifs{""},
      m_tokensSize{0},
      m_buf{""},
      m_endOfFile{false} {}

Tokenizer::Tokenizer(const std::string &file_name)
    : m_fileName{file_name},
      m_ifs{file_name},
      m_tokensSize{0},
      m_buf{""},
      m_endOfFile{false} {}

void Tokenizer::backslash() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::Backslash));
}

void Tokenizer::backslash(GroupToken &parentGtok) {
    insertSingleTokenToParent(parentGtok, Token::Type::Backslash);
}

void Tokenizer::clearBuf() { m_buf.clear(); }

void Tokenizer::colon() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::Colon));
}

void Tokenizer::colon(GroupToken &parentGtok) {
    insertSingleTokenToParent(parentGtok, Token::Type::Colon);
}

void Tokenizer::comma() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::Comma));
}

void Tokenizer::comma(GroupToken &parentGtok) {
    insertSingleTokenToParent(parentGtok, Token::Type::Comma);
}

void Tokenizer::comment() {
    // Assume unquoted and numSign
    // is consumed

    GroupToken commentToken{Token::Type::Comment};

    while (m_char != '\n') {  // Stop at indent
        scalar(commentToken);
        sym(commentToken);
        whitespace(commentToken);
    }

    insertGroupTokenToTokens(createGroupToken(commentToken));
}

void Tokenizer::comment(GroupToken &parentGtok) {
    GroupToken commentToken{Token::Type::Comment};

    while (m_char != '\n') {  // Stop at indent
        scalar(commentToken);
        sym(commentToken);
        whitespace(commentToken);
    }

    insertGroupTokenToParent(parentGtok, createGroupToken(commentToken));
}

std::unique_ptr<GroupToken> Tokenizer::createGroupToken(
    const Token::Type &tokenType) const {
    return std::make_unique<GroupToken>(GroupToken{tokenType});
}

std::unique_ptr<GroupToken> Tokenizer::createGroupToken(GroupToken &gtok) {
    return std::make_unique<GroupToken>(gtok);
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

std::unique_ptr<SingleToken> Tokenizer::createSingleToken(SingleToken &stok) {
    return std::make_unique<SingleToken>(stok);
}

void Tokenizer::dash() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::Dash));
}

void Tokenizer::dash(GroupToken &parentGtok) {
    insertSingleTokenToParent(parentGtok, Token::Type::Dash);
}

void Tokenizer::doubleQuote() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::DoubleQuote));
}

void Tokenizer::doubleQuote(GroupToken &parentGtok) {
    insertSingleTokenToParent(parentGtok, Token::Type::DoubleQuote);
}

std::vector<std::unique_ptr<Token>> Tokenizer::getTokens() const {
    // Copy every single unique_ptr from m_tokens
    // and every GroupToken within it

    std::vector<std::unique_ptr<Token>> newTokenVector;

    for (const auto &token : m_tokens) {
        if (token != nullptr) {
            newTokenVector.push_back(token->clone());
        }
    }

    return newTokenVector;
}

void Tokenizer::insertGroupTokenToParent(GroupToken &parentGtok,
                                         const Token::Type &tokenType) {
    parentGtok.insertToTokenGroup(createGroupToken(tokenType));
}

void Tokenizer::insertGroupTokenToParent(
    GroupToken &parentGtok, const std::unique_ptr<GroupToken> &gtokPtr) {
    parentGtok.insertToTokenGroup(gtokPtr->clone());
}

void Tokenizer::insertGroupTokenToParent(
    GroupToken &parentGtok, std::unique_ptr<GroupToken> &&gtokPtr) {
    parentGtok.insertToTokenGroup(std::move(gtokPtr));
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

void Tokenizer::insertSingleTokenToParent(GroupToken &parentGtok,
                                          const Token::Type &tokenType) {
    parentGtok.insertToTokenGroup(createSingleToken(tokenType));
}

void Tokenizer::insertSingleTokenToParent(GroupToken &parentGtok,
                                          const Token::Type &tokenType,
                                          std::string &&data) {
    parentGtok.insertToTokenGroup(
        createSingleToken(tokenType, std::move(data)));
}

void Tokenizer::insertSingleTokenToParent(
    GroupToken &parentGtok, const std::unique_ptr<SingleToken> &stokPtr) {
    parentGtok.insertToTokenGroup(stokPtr->clone());
}

void Tokenizer::insertSingleTokenToParent(
    GroupToken &parentGtok, std::unique_ptr<SingleToken> &&stokPtr) {
    parentGtok.insertToTokenGroup(std::move(stokPtr));
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

void Tokenizer::leftBrace() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::LeftBrace));
}

void Tokenizer::leftBrace(GroupToken &parentGtok) {
    insertSingleTokenToParent(parentGtok, Token::Type::LeftBrace);
}

void Tokenizer::leftBracket() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::LeftBracket));
}

void Tokenizer::leftBracket(GroupToken &parentGtok) {
    insertSingleTokenToParent(parentGtok, Token::Type::LeftBracket);
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

void Tokenizer::newline() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::Newline));
}

void Tokenizer::next() {
    m_ifs.get(m_char);
    if (m_ifs.eof()) {
        m_endOfFile = true;
        throw EndOfIfstreamException();
    }
}

void Tokenizer::numSign() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::NumSign));
}

void Tokenizer::numSign(GroupToken &parentGtok) {
    insertSingleTokenToParent(parentGtok, Token::Type::NumSign);
}

void Tokenizer::otherSymbols() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::Symbol));
}

void Tokenizer::otherSymbols(GroupToken &parentGtok) {
    insertSingleTokenToParent(parentGtok, Token::Type::Symbol);
}

void Tokenizer::rightBrace() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::RightBrace));
}

void Tokenizer::rightBrace(GroupToken &parentGtok) {
    insertSingleTokenToParent(parentGtok, Token::Type::RightBrace);
}

void Tokenizer::rightBracket() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::RightBracket));
}

void Tokenizer::rightBracket(GroupToken &parentGtok) {
    insertSingleTokenToParent(parentGtok, Token::Type::RightBracket);
}

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

    insertSingleTokenToTokens(
        createSingleToken(Token::Type::Scalar, std::move(m_buf)));
    clearBuf();  // Clear the buffer after creating the token
}

void Tokenizer::scalar(GroupToken &parentGtok) {
    if (!isAlnum(m_char)) return;
    while (isAlnum(m_char)) {
        m_buf += m_char;

        try {
            next();
        } catch (const EndOfIfstreamException &) {
            return;
        }
    }

    insertSingleTokenToParent(parentGtok,
                              createSingleToken(Token::Type::Scalar));
    clearBuf();
}

void Tokenizer::singleQuote() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::SingleQuote));
}

void Tokenizer::singleQuote(GroupToken &parentGtok) {
    insertSingleTokenToParent(parentGtok, Token::Type::SingleQuote);
}

void Tokenizer::sym() {
    if (!isSymbol(m_char)) return;

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

void Tokenizer::sym(GroupToken &parentGtok) {
    if (!isSymbol(m_char)) return;

    switch (m_char) {
        case '\\':
            backslash(parentGtok);
            break;
        case ':':
            colon(parentGtok);
            break;
        case ',':
            comma(parentGtok);
            break;
        case '-':
            dash(parentGtok);
            break;
        case '"':
            doubleQuote(parentGtok);
            break;
        case '{':
            leftBrace(parentGtok);
            break;
        case '[':
            leftBracket(parentGtok);
            break;
        case '#':
            numSign(parentGtok);
            break;
        case '}':
            rightBrace(parentGtok);
            break;
        case ']':
            rightBracket(parentGtok);
            break;
        case '\'':
            singleQuote(parentGtok);
            break;
        default:
            otherSymbols(parentGtok);
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

void Tokenizer::space() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::Space));
}

void Tokenizer::space(GroupToken &parentGtok) {
    insertSingleTokenToParent(parentGtok, Token::Type::Space);
}

void Tokenizer::tab() {
    insertSingleTokenToTokens(createSingleToken(Token::Type::Tab));
}

void Tokenizer::tab(GroupToken &parentGtok) {
    insertSingleTokenToParent(parentGtok, Token::Type::Tab);
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

void Tokenizer::whitespace(GroupToken &parentGtok) {
    while (isSpace(m_char)) {
        switch (m_char) {
            case '\n':
                newline(parentGtok);
                break;
            case ' ':
                space(parentGtok);
                break;
            case '\t':
                tab(parentGtok);
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

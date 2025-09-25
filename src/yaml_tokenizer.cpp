/*   Created:  07-23-2025
 *   Modified: 09-25-2025
 */

#include "yaml_tokenizer.hpp"

#include <memory>
#include <new>
#include <utility>

#include "yaml_except.hpp"

// TODO: m_depth and indent()
// TODO: rename exception members

namespace YAML {

Token::Token() {}

Token::Token(const Token::Class &cls) : m_class{cls} {}

Token::Token(const Token::Type &type) : m_type{type} {}

Token::Token(const Token::Class &cls, const Token::Type &type)
    : m_class{cls}, m_type{type} {}

Token::~Token() {}

SingleToken::SingleToken() : Token(Token::Class::Single) {}

SingleToken::SingleToken(const Token::Type &type)
    : Token(Token::Class::Single, type), m_data{""} {}

SingleToken::SingleToken(const Token::Type &type, const std::string &data)
    : Token(Token::Class::Single, type), m_data{data} {}

SingleToken::SingleToken(const Token::Type &type, std::string &&data)
    : Token(Token::Class::Single, type), m_data{std::move(data)} {}

SingleToken::SingleToken(const SingleToken &other)
    : Token(Token::Class::Single, other.m_type), m_data{other.m_data} {}

SingleToken &SingleToken::operator=(const SingleToken &other) {
    if (this != &other) {
        m_class = Token::Class::Single;  // might not be necessary
        m_data = other.m_data;
        m_type = other.m_type;
    }

    return *this;
}

std::shared_ptr<Token> SingleToken::clone() const {
    try {
        return std::make_shared<SingleToken>(*this);
    } catch (const std::bad_alloc &e) {
        throw FailedAllocException();
        // return nullptr;
    }
}

const std::string &SingleToken::getData() const { return m_data; }

void SingleToken::setData(const std::string &data) { m_data = data; }

Token::Class SingleToken::getClass() const { return m_class; }

Token::Type SingleToken::getType() const { return m_type; }

void SingleToken::setType(const Token::Type &type) { m_type = type; }

SingleToken::~SingleToken() {}

GroupToken::GroupToken() : Token(Token::Class::Group) {}

GroupToken::GroupToken(const Token::Type &type)
    : Token(Token::Class::Group, type) {}

// Do not call clone()
// This will not copy members directly into the current object

GroupToken::GroupToken(const GroupToken &other)
    : Token(Token::Class::Group, other.m_type),
      // Deep copy required
      m_tokenGroup{copyTokenGroup()},
      m_tokenGroupSize{other.m_tokenGroupSize} {}

GroupToken::GroupToken(GroupToken &&other) noexcept
    : Token(Token::Class::Group, other.m_type) {
    for (auto &token : other.m_tokenGroup) {
        // Each sub-GroupToken owns its own tokens
        // therefore, no copying is necessary
        m_tokenGroup.push_back(std::move(token));
    }

    m_tokenGroupSize = other.m_tokenGroupSize;
}

GroupToken &GroupToken::operator=(const GroupToken &other) {
    if (this != &other) {
        m_class = Token::Class::Group;
        m_type = other.m_type;
        clearTokenGroup();
        m_tokenGroup = copyTokenGroup();
    }

    return *this;
}

GroupToken &GroupToken::operator=(GroupToken &&other) noexcept {
    if (this != &other) {
        m_class = Token::Class::Group;
        m_type = std::move(other.m_type);
        clearTokenGroup();
        m_tokenGroup = std::move(other.m_tokenGroup);
        m_tokenGroupSize = other.m_tokenGroupSize;
    }

    return *this;
}

void GroupToken::clearTokenGroup() { m_tokenGroup.clear(); }

std::vector<std::shared_ptr<Token>> GroupToken::copyTokenGroup() const {
    std::vector<std::shared_ptr<Token>> newTokenVector;

    for (const auto &token : m_tokenGroup) {
        newTokenVector.push_back(token->clone());
    }

    return newTokenVector;
}

const std::vector<std::shared_ptr<Token>> &GroupToken::getTokenGroup() const {
    return m_tokenGroup;
}

void GroupToken::insertToTokenGroup(std::shared_ptr<Token> &&token) {
    if (token != nullptr) {
        m_tokenGroup.push_back(std::move(token));
        ++m_tokenGroupSize;
    }
}

bool GroupToken::empty() const { return m_tokenGroupSize <= 0; }

size_t GroupToken::sizeOfTokenGroup() const { return m_tokenGroupSize; }

std::shared_ptr<Token> GroupToken::clone() const {
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
        return std::make_shared<GroupToken>(newGroupToken);
    } catch (const std::bad_alloc &e) {
        throw FailedAllocException();
        // return nullptr;
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
      m_endOfFile{false} {
    insertGroupToken(Token::Type::Root);
}

Tokenizer::Tokenizer(const std::string &file_name)
    : m_fileName{file_name},
      m_ifs{file_name},
      m_tokensSize{0},
      m_buf{""},
      m_endOfFile{false} {
    insertGroupToken(Token::Type::Root);
}

void Tokenizer::backslash() { insertSingleToken(Token::Type::Backslash); }

void Tokenizer::clearBuf() { m_buf.clear(); }

void Tokenizer::colon() { insertSingleToken(Token::Type::Colon); }

void Tokenizer::comma() { insertSingleToken(Token::Type::Comma); }

void Tokenizer::comment() {
    // Assume unquoted and numSign
    // is consumed

    GroupToken commentToken{Token::Type::Comment};
    std::shared_ptr<GroupToken> commentTokenPtr =
        createGroupToken(commentToken);  // Allocate the pointer
    groupStack.push(commentTokenPtr);

    while (m_char != '\n') {  // Stop at indent
        scalar();
        sym();
        whitespace();
    }

    groupStack.pop();  // Pop out parent commentToken

    insertGroupToken(commentTokenPtr);
}

std::shared_ptr<GroupToken> Tokenizer::createGroupToken(
    const Token::Type &type) const {
    try {
        return std::make_shared<GroupToken>(GroupToken{type});
    } catch (const std::bad_alloc &e) {
        throw FailedAllocException();
        // return nullptr;
    }
}

std::shared_ptr<GroupToken> Tokenizer::createGroupToken(GroupToken &gtok) {
    try {
        return std::make_shared<GroupToken>(gtok);
    } catch (const std::bad_alloc &e) {
        throw FailedAllocException();
        // return nullptr;
    }
}

std::shared_ptr<SingleToken> Tokenizer::createSingleToken(
    const Token::Type &type) const {
    try {
        return std::make_shared<SingleToken>(SingleToken{type});
    } catch (const std::bad_alloc &e) {
        throw FailedAllocException();
        // return nullptr;
    }
}

std::shared_ptr<SingleToken> Tokenizer::createSingleToken(
    const Token::Type &type, std::string &&data) const {
    try {
        return std::make_shared<SingleToken>(
            SingleToken{type, std::move(data)});
    } catch (const std::bad_alloc &e) {
        throw FailedAllocException();
        // return nullptr;
    }
}

std::shared_ptr<SingleToken> Tokenizer::createSingleToken(SingleToken &stok) {
    try {
        return std::make_shared<SingleToken>(stok);
    } catch (const std::bad_alloc &e) {
        throw FailedAllocException();
        // return nullptr;
    }
}

void Tokenizer::dash() { insertSingleToken(Token::Type::Dash); }

void Tokenizer::doubleQuote() { insertSingleToken(Token::Type::DoubleQuote); }

const std::vector<std::shared_ptr<Token>> &Tokenizer::getTokens() const {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    } else if (groupStack.size() > 1) {
        throw RootNotFoundException();
    }

    return groupStack.top()->getTokenGroup();
}

void Tokenizer::indent() {
    GroupToken indentToken{Token::Type::Indent};

    // Indents comprise of only spaces
    for (int i = 0; i < m_indent && m_char == ' '; ++i) {
        indentToken.insertToTokenGroup(createSingleToken(Token::Type::Space));
    }

    insertGroupToken(createGroupToken(std::move(indentToken)));
}

void Tokenizer::insertGroupToken(const Token::Type &type) {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<GroupToken> parent = groupStack.top();

    if (parent == nullptr) {
        throw NullTokenException("Parent GroupToken is a null pointer.");
    }

    parent->insertToTokenGroup(createGroupToken(type));
}

void Tokenizer::insertGroupToken(const std::shared_ptr<GroupToken> &gtokPtr) {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<GroupToken> parent = groupStack.top();

    if (parent == nullptr) {
        throw NullTokenException("Parent GroupToken is a null pointer.");
    }

    if (gtokPtr != parent) {
        parent->insertToTokenGroup(gtokPtr);
    }
}

void Tokenizer::insertSingleToken(const Token::Type &type) {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<GroupToken> parent = groupStack.top();

    if (parent == nullptr) {
        throw NullTokenException("Parent GroupToken is a null pointer.");
    }

    parent->insertToTokenGroup(createSingleToken(type));
}

void Tokenizer::insertSingleToken(const Token::Type &type, std::string &&data) {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<GroupToken> parent = groupStack.top();

    if (parent == nullptr) {
        throw NullTokenException("Parent GroupToken is a null pointer.");
    }

    parent->insertToTokenGroup(createSingleToken(type, std::move(data)));
}

void Tokenizer::insertSingleToken(const std::shared_ptr<SingleToken> &stokPtr) {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<GroupToken> parent = groupStack.top();

    if (parent == nullptr) {
        throw NullTokenException("Parent GroupToken is a null pointer.");
    }

    parent->insertToTokenGroup(stokPtr);
}

void Tokenizer::leftBrace() { insertSingleToken(Token::Type::LeftBrace); }

void Tokenizer::leftBracket() { insertSingleToken(Token::Type::LeftBracket); }

const char Tokenizer::lookahead() {
    // Looks ahead of the current character from ifstream
    int nextChar = m_ifs.peek();
    if (nextChar == std::char_traits<char>::eof()) {
        m_endOfFile = true;
        throw EndOfIfstreamException();
    }

    return static_cast<char>(nextChar);
}

void Tokenizer::mapping() {
    GroupToken keyToken{Token::Type::Key};

    // A mapping consists of a key and token;
    // therefore, the key token will be processed first
    // and along with it, the value.

    std::shared_ptr<GroupToken> keyTokenPtr = createGroupToken(keyToken);

    groupStack.push(keyTokenPtr);

    while (m_char != ':') {
        scalar();
        sym();
        whitespace();
    }

    groupStack.pop();

    colon();    // Consume colon token
    newline();  // Consume newline token
    indent();   // Consume any indents before the value

    insertGroupToken(std::move(keyTokenPtr));  // insert the token
    // move so it doesnt copy every token

    GroupToken valueToken{Token::Type::Value};
    std::shared_ptr<GroupToken> valueTokenPtr = createGroupToken(valueToken);

    groupStack.push(valueTokenPtr);

    // TODO: Value logic here (check depth)

    groupStack.pop();

    insertGroupToken(std::move(valueTokenPtr));
}

void Tokenizer::newline() { insertSingleToken(Token::Type::Newline); }

void Tokenizer::next() {
    m_ifs.get(m_char);
    if (m_ifs.eof()) {
        m_endOfFile = true;
        throw EndOfIfstreamException();
    }
}

void Tokenizer::numSign() { insertSingleToken(Token::Type::NumSign); }

void Tokenizer::otherSymbols() { insertSingleToken(Token::Type::Symbol); }

void Tokenizer::rightBrace() { insertSingleToken(Token::Type::RightBrace); }

void Tokenizer::rightBracket() { insertSingleToken(Token::Type::RightBracket); }

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

    insertSingleToken(createSingleToken(Token::Type::Scalar, std::move(m_buf)));
    clearBuf();  // Clear the buffer after creating the token
}

void Tokenizer::singleQuote() { insertSingleToken(Token::Type::SingleQuote); }

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

    clearBuf();  // Clear the buffer.

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

void Tokenizer::space() { insertSingleToken(Token::Type::Space); }

void Tokenizer::tab() { insertSingleToken(Token::Type::Tab); }

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

        clearBuf();  // Clear the buffer.

        try {
            next();
        } catch (const EndOfIfstreamException &) {
            return;
        }
    }
}

Tokenizer::~Tokenizer() {}
}  // namespace YAML

/*   Created:  07-23-2025
 *   Modified: 09-25-2025
 */

#include "yaml_tokenizer.hpp"

#include <filesystem>
#include <memory>
#include <new>
#include <utility>

#include "yaml_except.hpp"

// TODO: m_depth and indent()
// TODO: rename exception members

namespace YAML {

Token::Token(const std::shared_ptr<Token> &parent, const Token::Class &cls)
    : m_class{cls}, m_parent{parent} {}

Token::Token(const std::shared_ptr<Token> &parent, const Token::Type &type)
    : m_parent{parent}, m_type{type} {}

Token::Token(const std::shared_ptr<Token> &parent, const Token::Class &cls,
             const Token::Type &type)
    : m_class{cls}, m_parent{parent}, m_type{type} {}

Token::~Token() {}

SingleToken::SingleToken(const std::shared_ptr<Token> &parent,
                         const Token::Type &type)
    : Token(parent, Token::Class::Single, type), m_data{""} {}

SingleToken::SingleToken(const std::shared_ptr<Token> &parent,
                         const Token::Type &type, const std::string &data)
    : Token(parent, Token::Class::Single, type), m_data{data} {}

SingleToken::SingleToken(const std::shared_ptr<Token> &parent,
                         const Token::Type &type, std::string &&data)
    : Token(parent, Token::Class::Single, type), m_data{std::move(data)} {}

SingleToken::SingleToken(const SingleToken &other)
    : Token(other.m_parent, Token::Class::Single, other.m_type),
      m_data{other.m_data} {}

SingleToken &SingleToken::operator=(const SingleToken &other) {
    if (this != &other) {
        m_class = Token::Class::Single;  // might not be necessary
        m_data = other.m_data;
        m_parent = other.m_parent;
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

int SingleToken::getDepth() const { return m_depth; }

const std::shared_ptr<Token> &SingleToken::getParent() const {
    return m_parent;
}

Token::Type SingleToken::getType() const { return m_type; }

void SingleToken::setDepth(const int &depth) { m_depth = depth; }

void SingleToken::setParent(const std::shared_ptr<Token> &parent) {
    m_parent = parent;
}

void SingleToken::setType(const Token::Type &type) { m_type = type; }

SingleToken::~SingleToken() {}

GroupToken::GroupToken(const std::shared_ptr<Token> &parent,
                       const Token::Type &type)
    : Token(parent, Token::Class::Group, type) {}

// Do not call clone()
// This will not copy members directly into the current object

GroupToken::GroupToken(const GroupToken &other)
    : Token(other.m_parent, Token::Class::Group, other.m_type),
      // Deep copy required
      m_tokens{copy()},
      m_size{other.m_size} {}

GroupToken::GroupToken(GroupToken &&other) noexcept
    : Token(std::move(other.m_parent), Token::Class::Group,
            std::move(other.m_type)),
      m_tokens{std::move(other.m_tokens)},
      m_size{std::move(other.m_size)} {}

GroupToken &GroupToken::operator=(const GroupToken &other) {
    if (this != &other) {
        m_class = Token::Class::Group;
        m_parent = other.m_parent;
        m_size = other.m_size;
        m_type = other.m_type;
        clear();  // Wipe the old tokens out
        m_tokens = copy();
    }

    return *this;
}

GroupToken &GroupToken::operator=(GroupToken &&other) noexcept {
    if (this != &other) {
        m_class = Token::Class::Group;
        m_size = other.m_size;
        m_type = std::move(other.m_type);
        clear();
        m_tokens = std::move(other.m_tokens);
    }

    return *this;
}

void GroupToken::clear() {
    m_tokens.clear();
    m_size = 0;
}

std::vector<std::shared_ptr<Token>> GroupToken::copy() const {
    std::vector<std::shared_ptr<Token>> newTokenVector;

    for (const auto &token : m_tokens) {
        newTokenVector.push_back(token->clone());
    }

    return newTokenVector;
}

const std::vector<std::shared_ptr<Token>> &GroupToken::getTokens() const {
    return m_tokens;
}

void GroupToken::insert(std::shared_ptr<Token> &&token) {
    if (token != nullptr) {
        m_tokens.push_back(std::move(token));
        ++m_size;
    }
}

bool GroupToken::empty() const { return m_size <= 0; }

size_t GroupToken::size() const { return m_size; }

std::shared_ptr<Token> GroupToken::clone() const {
    // Make a new GroupToken
    // Do not call copy constructor
    // It does not use recursion directly

    // FIXME: Make GroupToken constructor with parent
    GroupToken newGroupToken{};

    newGroupToken.setType(m_type);

    for (const auto &token : m_tokens) {
        if (token == nullptr) {
            // TODO: Error here
        }
        // If this is a GroupToken, recursively add all subtokens
        newGroupToken.insert(token->clone());
    }

    try {
        return std::make_shared<GroupToken>(newGroupToken);
    } catch (const std::bad_alloc &e) {
        throw FailedAllocException();
        // return nullptr;
    }
}

Token::Class GroupToken::getClass() const { return m_class; }

int GroupToken::getDepth() const { return m_depth; }

const std::shared_ptr<Token> &GroupToken::getParent() const { return m_parent; }

Token::Type GroupToken::getType() const { return m_type; }

void GroupToken::setDepth(const int &depth) { m_depth = depth; }

void GroupToken::setParent(const std::shared_ptr<Token> &parent) {
    m_parent = parent;
}

void GroupToken::setType(const Token::Type &type) { m_type = type; }

GroupToken::~GroupToken() {}

Tokenizer::Tokenizer()
    : m_fileName{""}, m_ifs{""}, m_size{0}, m_buf{""}, m_endOfFile{false} {
    insertGroupToken(Token::Type::Root);
}

Tokenizer::Tokenizer(const std::string &file_name)
    : m_fileName{file_name},
      m_ifs{file_name},
      m_size{0},
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

    return groupStack.top()->getTokens();
}

void Tokenizer::indent() {
    GroupToken indentToken{Token::Type::Indent};

    // Indents comprise of only spaces
    for (int i = 0; i < m_indent && m_char == ' '; ++i) {
        indentToken.insert(createSingleToken(Token::Type::Space));
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

    parent->insert(createGroupToken(type));
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
        parent->insert(gtokPtr);
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

    parent->insert(createSingleToken(type));
}

void Tokenizer::insertSingleToken(const Token::Type &type, std::string &&data) {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<GroupToken> parent = groupStack.top();

    if (parent == nullptr) {
        throw NullTokenException("Parent GroupToken is a null pointer.");
    }

    parent->insert(createSingleToken(type, std::move(data)));
}

void Tokenizer::insertSingleToken(const std::shared_ptr<SingleToken> &stokPtr) {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<GroupToken> parent = groupStack.top();

    if (parent == nullptr) {
        throw NullTokenException("Parent GroupToken is a null pointer.");
    }

    parent->insert(stokPtr);
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

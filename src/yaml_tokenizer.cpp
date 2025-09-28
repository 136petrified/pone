/*   Created:  07-23-2025
 *   Modified: 09-27-2025
 */

#include "yaml_tokenizer.hpp"

#include <memory>
#include <new>
#include <utility>

#include "yaml_except.hpp"

// TODO: rename exception members

namespace YAML {

Token::Token(const std::shared_ptr<Token> &parent, const std::string &name,
             const Token::Class &cls)
    : m_class{cls}, m_name{name}, m_parent{parent} {}

Token::Token(const std::shared_ptr<Token> &parent, const std::string &name,
             const Token::Type &type)
    : m_name{name}, m_parent{parent}, m_type{type} {}

Token::Token(const std::shared_ptr<Token> &parent, const std::string &name,
             const Token::Class &cls, const Token::Type &type)
    : m_class{cls}, m_name{name}, m_parent{parent}, m_type{type} {}

Token::~Token() {}

SingleToken::SingleToken(const std::shared_ptr<Token> &parent,
                         const Token::Type &type)
    : Token(parent, setName(), Token::Class::Single, type), m_data{""} {}

SingleToken::SingleToken(const std::shared_ptr<Token> &parent,
                         const Token::Type &type, const std::string &data)
    : Token(parent, setName(), Token::Class::Single, type), m_data{data} {}

SingleToken::SingleToken(const std::shared_ptr<Token> &parent,
                         const Token::Type &type, std::string &&data)
    : Token(parent, setName(), Token::Class::Single, type),
      m_data{std::move(data)} {}

SingleToken::SingleToken(const SingleToken &other)
    : Token(other.m_parent, setName(), Token::Class::Single, other.m_type),
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

std::shared_ptr<Token> SingleToken::clone(std::shared_ptr<Token> parent) const {
    std::shared_ptr<Token> pRoot = std::make_shared<SingleToken>(*this);
    pRoot->setParent(parent);
    return pRoot;
}

const std::string &SingleToken::getData() const { return m_data; }

void SingleToken::setData(const std::string &data) { m_data = data; }

Token::Class SingleToken::getClass() const { return m_class; }

int SingleToken::getDepth() const { return m_depth; }

const std::string &SingleToken::getName() const { return m_name; }

const std::shared_ptr<Token> &SingleToken::getParent() const {
    return m_parent;
}

std::shared_ptr<Token> SingleToken::getPtr() const {
    try {
        return std::static_pointer_cast<Token>(shared_from_this());
    } catch (const std::bad_weak_ptr &e) {
        throw FailedAllocException();
    }
}

Token::Type SingleToken::getType() const { return m_type; }

void SingleToken::setDepth() {
    m_depth = (m_parent == nullptr) ? 0 : m_parent->getDepth() + 1;
}

std::string SingleToken::setName() const { return tokenNameMap.at(m_type); }

void SingleToken::setParent(const std::shared_ptr<Token> &parent) {
    m_parent = parent;
}

void SingleToken::setType(const Token::Type &type) { m_type = type; }

SingleToken::~SingleToken() {}

GroupToken::GroupToken(const std::shared_ptr<Token> &parent,
                       const Token::Type &type)
    : Token(parent, setName(), Token::Class::Group, type) {}

// Do not call clone()
// This will not copy members directly into the current object

GroupToken::GroupToken(const GroupToken &other)
    : Token(other.m_parent, setName(), Token::Class::Group, other.m_type),
      // Deep copy required
      m_tokens{copy()},
      m_size{other.m_size} {}

GroupToken::GroupToken(GroupToken &&other) noexcept
    : Token(std::move(other.m_parent), setName(), Token::Class::Group,
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
    std::shared_ptr<Token> curr = getPtr();

    for (const auto &token : m_tokens) {
        if (token != curr) {
            newTokenVector.push_back(token->clone(curr));
        }
    }

    return newTokenVector;
}

const std::vector<std::shared_ptr<Token>> &GroupToken::getTokens() const {
    return m_tokens;
}

void GroupToken::insert(std::shared_ptr<Token> token) {
    if (token == nullptr) {
        throw NullTokenException();
    }

    m_tokens.push_back(token);
    ++m_size;
}

bool GroupToken::empty() const { return m_size <= 0; }

size_t GroupToken::size() const { return m_size; }

std::shared_ptr<Token> GroupToken::clone(std::shared_ptr<Token> parent) const {
    std::shared_ptr<GroupToken> pRoot =
        std::make_shared<GroupToken>(GroupToken(parent, m_type));

    for (const auto &token : m_tokens) {
        pRoot->insert(token->clone(pRoot));
    }

    return pRoot;
}

Token::Class GroupToken::getClass() const { return m_class; }

int GroupToken::getDepth() const { return m_depth; }

const std::string &GroupToken::getName() const { return m_name; }

const std::shared_ptr<Token> &GroupToken::getParent() const { return m_parent; }

std::shared_ptr<Token> GroupToken::getPtr() const {
    try {
        return std::static_pointer_cast<Token>(shared_from_this());
    } catch (const std::bad_weak_ptr &e) {
        throw FailedAllocException();
    }
}

Token::Type GroupToken::getType() const { return m_type; }

void GroupToken::setDepth() {
    m_depth = (m_parent == nullptr) ? 0 : m_parent->getDepth() + 1;
}

std::string GroupToken::setName() const { return tokenNameMap.at(m_type); }

void GroupToken::setParent(const std::shared_ptr<Token> &parent) {
    m_parent = parent;
}

void GroupToken::setType(const Token::Type &type) { m_type = type; }

GroupToken::~GroupToken() {}

Tokenizer::Tokenizer()
    : m_fileName{""}, m_ifs{""}, m_size{0}, m_buf{""}, m_endOfFile{false} {
    insertGroupToken(Token::Type::Root);
}

Tokenizer::Tokenizer(const std::string &fileName)
    : m_fileName{fileName},
      m_ifs{fileName},
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
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    GroupToken commentToken{groupStack.top(), Token::Type::Comment};

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
        return std::make_shared<GroupToken>(GroupToken{groupStack.top(), type});
    } catch (const std::bad_alloc &e) {
        throw FailedAllocException();
    }
}

std::shared_ptr<GroupToken> Tokenizer::createGroupToken(GroupToken &gtok) {
    return std::dynamic_pointer_cast<GroupToken>(gtok.getPtr());
}

std::shared_ptr<SingleToken> Tokenizer::createSingleToken(
    const Token::Type &type) const {
    try {
        return std::make_shared<SingleToken>(
            SingleToken{groupStack.top(), type});
    } catch (const std::bad_alloc &e) {
        throw FailedAllocException();
    }
}

std::shared_ptr<SingleToken> Tokenizer::createSingleToken(
    const Token::Type &type, std::string &&data) const {
    try {
        return std::make_shared<SingleToken>(
            SingleToken{groupStack.top(), type, std::move(data)});
    } catch (const std::bad_alloc &e) {
        throw FailedAllocException();
    }
}

std::shared_ptr<SingleToken> Tokenizer::createSingleToken(SingleToken &stok) {
    return std::dynamic_pointer_cast<SingleToken>(stok.getPtr());
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
    GroupToken indentToken{groupStack.top(), Token::Type::Indent};

    // Indents comprise of only spaces
    for (int i = 0; i < m_indent && m_char == ' '; ++i) {
        indentToken.insert(createSingleToken(Token::Type::Space));
    }

    insertGroupToken(createGroupToken(indentToken));
    ++m_depth;  // Increases depth by one
}

void Tokenizer::insertGroupToken(const Token::Type &type) {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<Token> parent = groupStack.top();

    if (parent == nullptr) {
        throw NullTokenException("Parent GroupToken is a null pointer.");
    }

    parent->insert(createGroupToken(type));
}

void Tokenizer::insertGroupToken(const std::shared_ptr<GroupToken> &gtokPtr) {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<Token> parent = groupStack.top();

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

    if (groupStack.size() < 1) {
        throw RootNotFoundException();
    }

    std::shared_ptr<Token> parent = groupStack.top();

    if (parent == nullptr) {
        throw NullTokenException("Parent GroupToken is a null pointer.");
    }

    parent->insert(createSingleToken(type));
}

void Tokenizer::insertSingleToken(const Token::Type &type, std::string &&data) {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<Token> parent = groupStack.top();

    if (parent == nullptr) {
        throw NullTokenException("Parent GroupToken is a null pointer.");
    }

    parent->insert(createSingleToken(type, std::move(data)));
}

void Tokenizer::insertSingleToken(const std::shared_ptr<SingleToken> &stokPtr) {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<Token> parent = groupStack.top();

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
    GroupToken keyToken{groupStack.top(), Token::Type::Key};

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

    colon();       // Consume colon token
    whitespace();  // Consume any whitespace
    indent();      // Consume any indents before the value

    insertGroupToken(std::move(keyTokenPtr));  // insert the token
    // move so it doesnt copy every token

    GroupToken valueToken{groupStack.top(), Token::Type::Value};
    std::shared_ptr<GroupToken> valueTokenPtr = createGroupToken(valueToken);

    groupStack.push(valueTokenPtr);

    if (m_char == '-') {
        // TODO: Implement value logic
        // For sequences and regular values
    }

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

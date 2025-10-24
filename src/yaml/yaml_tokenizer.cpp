/*   Created:  07-23-2025
 *   Modified: 10-24-2025
 */

#include "yaml_tokenizer.hpp"
#include <algorithm>
#include <format>
#include <memory>
#include <new>
#include <utility>
#include "yaml_const.hpp"
#include "yaml_except.hpp"

namespace YAML {

Token::Token(const std::shared_ptr<Token> &parent,
             const std::string &name,
             const Token::Class &cls)
    : m_class{cls}, m_name{name}, m_parent{parent} {}

Token::Token(const std::shared_ptr<Token> &parent,
             const std::string &name,
             const Token::Type &type)
    : m_name{name}, m_parent{parent}, m_type{type} {}

Token::Token(const std::shared_ptr<Token> &parent,
             const std::string &name,
             const Token::Class &cls,
             const Token::Type &type)
    : m_class{cls}, m_name{name}, m_parent{parent}, m_type{type} {}

Token::~Token() {}

Token::Class Token::getClass() const {
    return m_class;
}

int Token::getDepth() const {
    return m_depth;
}

const std::string &Token::getName() const {
    return m_name;
}

const std::shared_ptr<Token> &Token::getParent() const {
    return m_parent;
}

Token::Type Token::getType() const {
    return m_type;
}

void Token::printEntry(std::ostream &out,
                       std::vector<std::string> &indent,
                       const std::string &prefix) const {
    std::size_t depth =
        std::min(static_cast<std::size_t>(m_depth), indent.size());

    for (std::size_t i = 0; i < depth; ++i) {
        out << indent[i];
    }

    out << prefix << " " << m_name;
}

void Token::setDepth() {
    m_depth = (m_parent == nullptr) ? 0 : m_parent->getDepth();
}

std::string Token::setName() const {
    return tokenNameMap.at(m_type);
}

void Token::setType(const Token::Type &type) {
    m_type = type;
}

SingleToken::SingleToken(const std::shared_ptr<Token> &parent,
                         const Token::Type &type)
    : Token(parent, setName(), Token::Class::Single, type), m_data{""} {}

SingleToken::SingleToken(const std::shared_ptr<Token> &parent,
                         const Token::Type &type,
                         const std::string &data)
    : Token(parent, setName(), Token::Class::Single, type), m_data{data} {}

SingleToken::SingleToken(const std::shared_ptr<Token> &parent,
                         const Token::Type &type,
                         std::string &&data)
    : Token(parent, setName(), Token::Class::Single, type),
      m_data{std::move(data)} {}

SingleToken::SingleToken(const SingleToken &other)
    : Token(other.m_parent, setName(), Token::Class::Single, other.m_type),
      m_data{other.m_data} {}

SingleToken &SingleToken::operator=(const SingleToken &other) {
    if (this != &other) {
        m_class  = Token::Class::Single;  // might not be necessary
        m_data   = other.m_data;
        m_parent = other.m_parent;
        m_type   = other.m_type;
    }

    return *this;
}

std::shared_ptr<Token> SingleToken::clone(std::shared_ptr<Token> parent) const {
    try {
        std::shared_ptr<Token> root = std::make_shared<SingleToken>(*this);
        root->setParent(parent);
        return root;
    } catch (const std::bad_alloc &e) {
        ErrorMessage emsg{name::YAML_GLOBAL_NAMESPACE, name::TOKEN_CLONE,
                          "Failed to allocate a SingleToken."};
        throw FailedAllocException(emsg);
    }
}

const std::string &SingleToken::getData() const {
    return m_data;
}

void SingleToken::setData(const std::string &data) {
    m_data = data;
}

std::shared_ptr<Token> SingleToken::getPtr() const {
    try {
        return std::static_pointer_cast<Token>(shared_from_this());
    } catch (const std::bad_weak_ptr &e) {
        ErrorMessage emsg{name::YAML_GLOBAL_NAMESPACE, name::TOKEN_GETPTR,
                          "Failed to allocate a pointer to SingleToken"};
        throw FailedAllocException(emsg);
    }
}

void SingleToken::print(std::ostream &out,
                        std::vector<std::string> &indent,
                        const std::string &prefix) const {
    printEntry(out, indent, prefix);
    out << '\n';
}

void SingleToken::setParent(const std::shared_ptr<Token> &parent) {
    m_parent = parent;
}

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
    : Token(std::move(other.m_parent),
            setName(),
            Token::Class::Group,
            std::move(other.m_type)),
      m_tokens{std::move(other.m_tokens)},
      m_size{std::move(other.m_size)} {}

GroupToken &GroupToken::operator=(const GroupToken &other) {
    if (this != &other) {
        m_class  = Token::Class::Group;
        m_parent = other.m_parent;
        m_size   = other.m_size;
        m_type   = other.m_type;
        clear();  // Wipe the old tokens out
        m_tokens = copy();
    }

    return *this;
}

GroupToken &GroupToken::operator=(GroupToken &&other) noexcept {
    if (this != &other) {
        m_class = Token::Class::Group;
        m_size  = other.m_size;
        m_type  = std::move(other.m_type);
        clear();
        m_tokens = std::move(other.m_tokens);
    }

    return *this;
}

void GroupToken::clear() {
    for (const auto &token : m_tokens) {
        if (token == nullptr) {
            ErrorMessage emsg{name::YAML_GLOBAL_NAMESPACE, name::TOKEN_CLEAR,
                              "Received nullptr at this "
                              "function."};
            throw NullTokenException(emsg);
        } else if (token->getClass() == Token::Class::Group) {
            token->clear();
        }

        m_tokens.clear();
        m_size = 0;
    }
}

std::vector<std::shared_ptr<Token>> GroupToken::copy() const {
    std::vector<std::shared_ptr<Token>> newTokenVector;
    std::shared_ptr<Token> curr = getPtr();  // Assume make_shared

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
        ErrorMessage emsg{name::YAML_GLOBAL_NAMESPACE, name::TOKEN_INSERT,
                          "Received nullptr at this "
                          "function."};

        throw NullTokenException(emsg);
    }

    m_tokens.push_back(token);
    ++m_size;
}

bool GroupToken::empty() const {
    return m_size <= 0;
}

void GroupToken::release() {
    if (m_parent == nullptr) {
        return;
    } else if (m_parent->getClass() == Token::Class::Single) {
        ErrorMessage emsg{
            name::YAML_GLOBAL_NAMESPACE, name::TOKEN_RELEASE,
            std::format(
                "Attempted to parse {}GroupToken but received {}SingleToken.",
                name::YAML_GLOBAL_NAMESPACE, name::YAML_GLOBAL_NAMESPACE)};
        throw NotAGroupException(emsg);
    }

    for (const auto &token : m_tokens) {
        m_parent->insert(token);
    }
}

std::size_t GroupToken::size() const {
    return m_size;
}

std::shared_ptr<Token> GroupToken::clone(std::shared_ptr<Token> parent) const {
    std::shared_ptr<GroupToken> root =
        std::make_shared<GroupToken>(GroupToken(parent, m_type));

    for (const auto &token : m_tokens) {
        root->insert(token->clone(root));
    }

    return root;
}

std::shared_ptr<Token> GroupToken::getPtr() const {
    try {
        return std::static_pointer_cast<Token>(shared_from_this());
    } catch (const std::bad_weak_ptr &e) {
        ErrorMessage emsg{name::YAML_GLOBAL_NAMESPACE, name::TOKEN_GETPTR,
                          "Failed to allocate a pointer to "
                          "GroupToken."};
        throw FailedAllocException(emsg);
    }
}

void GroupToken::print(std::ostream &out,
                       std::vector<std::string> &indent,
                       const std::string &prefix) const {
    printEntry(out, indent, prefix);

    std::string padding(m_name.size() + 2, ' ');
    if (m_depth > 0) {
        padding = std::string((prefix == "\u2514") ? " " : "\u2502") + padding;
    }

    if (!empty()) {
        out << "\u2510";
    }

    out << '\n';

    indent.push_back(padding);

    for (std::size_t i = 0; i < m_size; ++i) {
        m_tokens[i]->print(out, indent,
                           (i == m_size - 1) ? "\u2514" : "\u251c");
    }

    if (!indent.empty()) {
        indent.pop_back();
    }
}

void GroupToken::setParent(const std::shared_ptr<Token> &parent) {
    if (parent == getPtr()) {
        ErrorMessage emsg{name::YAML_GLOBAL_NAMESPACE, name::TOKEN_SETPARENT,
                          "Attempted to set a GroupToken's parent to "
                          "itself."};
        throw SelfParentInsertionException(emsg);
    }

    m_parent = parent;
}

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

void Tokenizer::backslash() {
    insertSingleToken(Token::Type::Backslash);
}

void Tokenizer::clearBuf() {
    m_buf.clear();
}

void Tokenizer::colon() {
    insertSingleToken(Token::Type::Colon);
}

void Tokenizer::comma() {
    insertSingleToken(Token::Type::Comma);
}

void Tokenizer::comment() {
    if (groupStack.empty()) {
        ErrorMessage emsg{name::YAML_GLOBAL_NAMESPACE, name::TOKENIZER_COMMENT,
                          "No parent found to insert a Token into."};
        throw EmptyGroupStackException(emsg);
    }

    std::shared_ptr<GroupToken> commentToken =
        createGroupToken(Token::Type::Comment);  // Allocate the pointer

    groupStack.push(commentToken);

    while (m_char != '\n') {  // Stop at indent
        literal();
    }

    groupStack.pop();  // Pop out parent commentToken

    insertGroupToken(commentToken);
}

std::shared_ptr<GroupToken> Tokenizer::createGroupToken(
    const Token::Type &type) const {
    try {
        return std::make_shared<GroupToken>(GroupToken{groupStack.top(), type});
    } catch (const std::bad_alloc &e) {
        ErrorMessage emsg{name::YAML_GLOBAL_NAMESPACE,
                          name::TOKENIZER_CREATEGROUPTOKEN,
                          "Failed to allocate GroupToken."};
        throw FailedAllocException(emsg);
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
        ErrorMessage emsg{name::YAML_GLOBAL_NAMESPACE,
                          name::TOKENIZER_CREATESINGLETOKEN,
                          "Failed to allocate SingleToken."};
        throw FailedAllocException(emsg);
    }
}

std::shared_ptr<SingleToken> Tokenizer::createSingleToken(
    const Token::Type &type,
    std::string &&data) const {
    try {
        return std::make_shared<SingleToken>(
            SingleToken{groupStack.top(), type, std::move(data)});
    } catch (const std::bad_alloc &e) {
        ErrorMessage emsg{name::YAML_GLOBAL_NAMESPACE,
                          name::TOKENIZER_CREATESINGLETOKEN_2,
                          "Failed to allocate SingleToken."};
        throw FailedAllocException(emsg);
    }
}

std::shared_ptr<SingleToken> Tokenizer::createSingleToken(SingleToken &stok) {
    return std::dynamic_pointer_cast<SingleToken>(stok.getPtr());
}

void Tokenizer::dash() {
    insertSingleToken(Token::Type::Dash);
}

void Tokenizer::doubleQuote() {
    insertSingleToken(Token::Type::DoubleQuote);
}

const std::shared_ptr<Token> &Tokenizer::getTokens() const {
    if (groupStack.empty()) {
        ErrorMessage emsg_1{name::YAML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_GETTOKENS,
                            "No parent found to insert a Token into."};
        throw EmptyGroupStackException(emsg_1);
    } else if (groupStack.size() > 1) {
        ErrorMessage emsg_2{name::YAML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_GETTOKENS,
                            "Attempted to insert into a GroupToken that was "
                            "not of type pone::YAML::Token::Type::Root."};
        throw RootNotFoundException(emsg_2);
    }

    return groupStack.top();  // Which is always root
}

void Tokenizer::indent() {
    GroupToken indentToken{groupStack.top(), Token::Type::Indent};

    // Indents comprise of only spaces
    for (int i = 0; i < m_indent && m_char == ' '; ++i) {
        indentToken.insert(createSingleToken(Token::Type::Space));
    }

    insertGroupToken(createGroupToken(indentToken));
}

void Tokenizer::insertGroupToken(const Token::Type &type) {
    if (groupStack.empty()) {
        ErrorMessage emsg_1{name::YAML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_GETTOKENS,
                            "No parent found to insert a Token into."};
        throw EmptyGroupStackException(emsg_1);
    }

    std::shared_ptr<Token> parent = groupStack.top();

    if (parent == nullptr) {
        ErrorMessage emsg_2{name::YAML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_GETTOKENS,
                            "Parent GroupToken is null."};

        throw NullTokenException(emsg_2);
    }

    parent->insert(createGroupToken(type));
}

void Tokenizer::insertGroupToken(const std::shared_ptr<GroupToken> &gtokPtr) {
    if (groupStack.empty()) {
        ErrorMessage emsg_1{name::YAML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_GETTOKENS,
                            "No parent found to insert a Token into."};
        throw EmptyGroupStackException(emsg_1);
    } else if (gtokPtr == nullptr) {
        // TODO: Continue adding ErrorMessage structs
    }

    std::shared_ptr<Token> parent = groupStack.top();

    if (parent == nullptr) {
        ErrorMessage emsg_3{name::YAML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_GETTOKENS,
                            "Parent GroupToken is null."};
        throw NullTokenException(emsg_3);
    }

    if (gtokPtr != parent) {
        parent->insert(gtokPtr);
    }
}

void Tokenizer::insertSingleToken(const Token::Type &type) {
    if (groupStack.empty()) {
        ErrorMessage emsg_1{name::YAML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_GETTOKENS,
                            "No parent found to insert a Token into."};
        throw EmptyGroupStackException(emsg_1);
    } else if (groupStack.size() < 1) {
        ErrorMessage emsg_2{
            name::YAML_GLOBAL_NAMESPACE, name::TOKENIZER_GETTOKENS,
            "Missing GroupToken of type pone::YAML::Token::Type::Root."};

        throw RootNotFoundException(emsg_2);
    }

    std::shared_ptr<Token> parent = groupStack.top();

    if (parent == nullptr) {
        throw NullTokenException(
            "YAML::yaml_tokenizer.cpp::"
            "insertSingleToken(const Token::Type &)",
            "Parent GroupToken is a null pointer.");
    }

    parent->insert(createSingleToken(type));
}

void Tokenizer::insertSingleToken(const Token::Type &type, std::string &&data) {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<Token> parent = groupStack.top();

    if (parent == nullptr) {
        throw NullTokenException(
            "YAML::yaml_tokenizer.cpp::"
            "insertSingletoken(const Token::Type &, "
            "std::string &&)",
            "Parent GroupToken is a null pointer.");
    }

    parent->insert(createSingleToken(type, std::move(data)));
}

void Tokenizer::insertSingleToken(const std::shared_ptr<SingleToken> &stokPtr) {
    if (groupStack.empty()) {
        throw EmptyGroupStackException(
            "YAML::yaml_tokenizer.cpp::insertSingleToken(const "
            "shared_ptr<SingleToken> &)");
    }

    std::shared_ptr<Token> parent = groupStack.top();

    if (parent == nullptr) {
        throw NullTokenException(
            "YAML::yaml_tokenizer.cpp::insertSingleToken(const "
            "shared_ptr<SingleToken> &)",
            "Parent GroupToken is a null pointer.");
    }

    parent->insert(stokPtr);
}

void Tokenizer::key() {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<GroupToken> keyToken = createGroupToken(Token::Type::Key);

    groupStack.push(keyToken);

    while (m_char != ':') {
        if (m_char == '\n') {
            // Reject the keyToken
            // and release tokens into parent Token

            keyToken->release();
            groupStack.pop();  // Discard the keyToken

            // The key failed, therefore the mapping does
            // throw malformed map exception
            // and have mapping() call catch this
            throw InvalidKeyException("YAML::yaml_tokenizer::key()",
                                      "No ':' found.");
        } else if (isQuote(m_char)) {
            quoted();
            return;
        }

        literal();
    }

    groupStack.pop();
    insertGroupToken(std::move(keyToken));
}

void Tokenizer::leftBrace() {
    insertSingleToken(Token::Type::LeftBrace);
}

void Tokenizer::leftBracket() {
    insertSingleToken(Token::Type::LeftBracket);
}

void Tokenizer::literal() {
    if (isAlnum(m_char)) {
        scalar();
    } else if (isSymbol(m_char)) {
        sym();
    } else if (isSpace(m_char)) {
        whitespace();
    }
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

void Tokenizer::mapping() {
    // A mapping consists of a key and token;
    // therefore, the key token will be processed first
    // and along with it, the value.

    while (!isSpace(m_char)) {
        whitespace();  // Consume all whitespace first
    }

    try {
        key();
    } catch (const InvalidMappingException &e) {
    }

    colon();  // Consume colon token
    try {
        next();
    } catch (const EndOfIfstreamException &) {
        return;  // Discard mapping
    }

    if (!isSpace(m_char)) {
        while (!isSpace(m_char)) {
            whitespace();  // Consume any whitespace
        }
    } else {
        throw InvalidMappingException();
    }

    value();
}

void Tokenizer::newline() {
    insertSingleToken(Token::Type::Newline);
}

void Tokenizer::next() {
    m_ifs.get(m_char);
    if (m_ifs.eof()) {
        m_endOfFile = true;
        throw EndOfIfstreamException();
    }
}

void Tokenizer::numSign() {
    insertSingleToken(Token::Type::NumSign);
}

void Tokenizer::otherSymbols() {
    insertSingleToken(Token::Type::Symbol);
}

void Tokenizer::print(std::ostream &out) const {
    std::shared_ptr<Token> root = getTokens();  // returns ptr to root
    std::vector<std::string> indentVector;
    root->print(out, indentVector, "");
}

void Tokenizer::quoted() {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<GroupToken> quotedToken =
        createGroupToken(Token::Type::Quoted);

    groupStack.push(quotedToken);

    if (m_char == '"') {
        doubleQuote();

        while (m_char != '"') {
            literal();
        }

        doubleQuote();  // Consume ending quote
    } else if (m_char == '\'') {
        singleQuote();

        while (m_char != '\'') {
            literal();
        }

        singleQuote();  // Consume ending quote
    } else {
        return;
    }

    groupStack.pop();
}

void Tokenizer::rightBrace() {
    insertSingleToken(Token::Type::RightBrace);
}

void Tokenizer::rightBracket() {
    insertSingleToken(Token::Type::RightBracket);
}

void Tokenizer::scalar() {
    if (!isAlnum(m_char))
        return;
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

void Tokenizer::sequence() {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<GroupToken> seqToken =
        createGroupToken(Token::Type::Sequence);

    groupStack.push(seqToken);

    // Must start with dash

    while (m_char == '-') {
        dash();  // Consume dash token
        try {
            next();
        } catch (const EndOfIfstreamException &) {
            groupStack.pop();  // seqToken
            return;
        }

        if (isSpace(m_char)) {
            whitespace();  // Consume whitespace token
        } else {
            groupStack.pop();  // Exit gracefully seqToken
            throw InvalidSequenceException();
        }

        seqElement();
    }

    groupStack.pop();

    insertGroupToken(seqToken);
}

void Tokenizer::seqElement() {
    if (groupStack.empty()) {
        throw EmptyGroupStackException();
    }

    std::shared_ptr<GroupToken> seqElemToken =
        createGroupToken(Token::Type::SeqElement);

    groupStack.push(seqElemToken);

    while (m_char != '-') {
        mapping();
        sequence();

        if (isAlnum(m_char)) {
            scalar();
        }
    }

    groupStack.pop();

    insertGroupToken(seqElemToken);  // when insert phase is finished
}

void Tokenizer::singleQuote() {
    insertSingleToken(Token::Type::SingleQuote);
}

void Tokenizer::sym() {
    if (!isSymbol(m_char))
        return;

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

void Tokenizer::space() {
    insertSingleToken(Token::Type::Space);
}

void Tokenizer::tab() {
    insertSingleToken(Token::Type::Tab);
}

void Tokenizer::tokenize() {
    try {
        next();  // Start with first token
    } catch (const EndOfIfstreamException &) {
        return;  // Means empty file
    }

    while (!m_endOfFile) {
        mapping();
        sequence();
        if (m_char == '#') {  // Must be symbol
            comment();        // This is to check for comments
            try {
                next();
            } catch (const EndOfIfstreamException &) {
                return;
            }
        }
    }
}

void Tokenizer::value() {
    std::shared_ptr<GroupToken> valueToken =
        createGroupToken(Token::Type::Value);
    groupStack.push(valueToken);

    if (m_char == '-') {
        sequence();
    } else if (isQuote(m_char)) {
        quoted();
        return;  // A value if quoted must end
    } else {
        while (m_char == '\n') {
            if (m_char == '#') {
                sym();  // Directly check for '#'
            } else if (isQuote(m_char)) {
                // Throw as this should not be in here
                throw InvalidMappingException();  // TODO: Probably
                                                  // add location
            }
            mapping();  // check mapping first
            literal();
        }
    }

    groupStack.pop();  // valueToken

    insertGroupToken(std::move(valueToken));
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

std::ostream &operator<<(std::ostream &out, const Tokenizer &tokenizer) {
    tokenizer.print(out);
    return out;
}

Tokenizer::~Tokenizer() {}
}  // namespace YAML

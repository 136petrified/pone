/* Created:  2026-05-23
 * Modified: 2026-05-24
 */

#include "toml_token.hpp"

namespace pone::TOML {

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

void Token::printEntry(std::ostream &out, std::vector<std::string> &indent,
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
    : Token(parent, setName(), Token::Class::SINGLE, type), m_data{""} {}

SingleToken::SingleToken(const std::shared_ptr<Token> &parent,
                         const Token::Type &type, const std::string &data)
    : Token(parent, setName(), Token::Class::SINGLE, type), m_data{data} {}

SingleToken::SingleToken(const std::shared_ptr<Token> &parent,
                         const Token::Type &type, std::string &&data)
    : Token(parent, setName(), Token::Class::SINGLE, type),
      m_data{std::move(data)} {}

SingleToken::SingleToken(const SingleToken &other)
    : Token(other.m_parent, setName(), Token::Class::SINGLE, other.m_type),
      m_data{other.m_data} {}

SingleToken &SingleToken::operator=(const SingleToken &other) {
    if (this != &other) {
        m_class = Token::Class::SINGLE; // might not be necessary
        m_data = other.m_data;
        m_parent = other.m_parent;
        m_type = other.m_type;
    }

    return *this;
}

std::shared_ptr<Token> SingleToken::clone(std::shared_ptr<Token> parent) const {
    try {
        std::shared_ptr<Token> root = std::make_shared<SingleToken>(*this);
        root->setParent(parent);
        return root;
    } catch (const std::bad_alloc &e) {
        ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE, name::TOKEN_CLONE,
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
        ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE, name::TOKEN_GETPTR,
                          "Failed to allocate a pointer to SingleToken"};
        throw FailedAllocException(emsg);
    }
}

void SingleToken::print(std::ostream &out, std::vector<std::string> &indent,
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
    : Token(parent, setName(), Token::Class::GROUP, type) {}

// Do not call clone()
// This will not copy members directly into the current object

GroupToken::GroupToken(const GroupToken &other)
    : Token(other.m_parent, setName(), Token::Class::GROUP, other.m_type),
      // Deep copy required
      m_tokens{copy()}, m_size{other.m_size} {}

GroupToken::GroupToken(GroupToken &&other) noexcept
    : Token(std::move(other.m_parent), setName(), Token::Class::GROUP,
            std::move(other.m_type)),
      m_tokens{std::move(other.m_tokens)}, m_size{std::move(other.m_size)} {}

GroupToken &GroupToken::operator=(const GroupToken &other) {
    if (this != &other) {
        m_class = Token::Class::GROUP;
        m_parent = other.m_parent;
        m_size = other.m_size;
        m_type = other.m_type;
        clear(); // Wipe the old tokens out
        m_tokens = copy();
    }

    return *this;
}

GroupToken &GroupToken::operator=(GroupToken &&other) noexcept {
    if (this != &other) {
        m_class = Token::Class::GROUP;
        m_size = other.m_size;
        m_type = std::move(other.m_type);
        clear();
        m_tokens = std::move(other.m_tokens);
    }

    return *this;
}

void GroupToken::clear() {
    for (const auto &token : m_tokens) {
        if (token == nullptr) {
            ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE, name::TOKEN_CLEAR,
                              "Received nullptr at this "
                              "function."};
            throw NullTokenException(emsg);
        } else if (token->getClass() == Token::Class::GROUP) {
            token->clear();
        }

        m_tokens.clear();
        m_size = 0;
    }
}

std::vector<std::shared_ptr<Token>> GroupToken::copy() const {
    std::vector<std::shared_ptr<Token>> newTokenVector;
    std::shared_ptr<Token> curr = getPtr(); // Assume make_shared

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
        ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE, name::TOKEN_INSERT,
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
    } else if (m_parent->getClass() == Token::Class::SINGLE) {
        ErrorMessage emsg{
            name::TOML_GLOBAL_NAMESPACE, name::TOKEN_RELEASE,
            std::format(
                "Attempted to parse {}GroupToken but received {}SingleToken.",
                name::TOML_GLOBAL_NAMESPACE, name::TOML_GLOBAL_NAMESPACE)};
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
        ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE, name::TOKEN_GETPTR,
                          "Failed to allocate a pointer to "
                          "GroupToken."};
        throw FailedAllocException(emsg);
    }
}

void GroupToken::print(std::ostream &out, std::vector<std::string> &indent,
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
        ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE, name::TOKEN_SETPARENT,
                          "Attempted to set a GroupToken's parent to "
                          "itself."};
        throw SelfParentInsertionException(emsg);
    }

    m_parent = parent;
}

GroupToken::~GroupToken() {}

} // namespace pone::TOML

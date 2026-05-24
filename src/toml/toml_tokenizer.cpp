/* Created:  2026-05-23
 * Modified: 2026-05-24
 */

#include "toml_tokenizer.hpp"
#include "toml_const.hpp"
#include "toml_except.hpp"
#include "toml_utils.hpp"

namespace pone::TOML {

Tokenizer::Tokenizer()
    : m_fileName{""}, m_ifs{""}, m_size{0}, m_buf{""}, m_endOfFile{false} {
    insertGroupToken(Token::Type::ROOT);
}

Tokenizer::Tokenizer(const std::string &fileName)
    : m_fileName{fileName}, m_ifs{fileName}, m_size{0}, m_buf{""},
      m_endOfFile{false} {
    insertGroupToken(Token::Type::ROOT);
}

void Tokenizer::clearBuf() {
    m_buf.clear();
}

void Tokenizer::comma() {
    insertSingleToken(Token::Type::COMMA);
}

void Tokenizer::comment() {
    if (groupStack.empty()) {
        ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE, name::TOKENIZER_COMMENT,
                          "No parent found to insert a Token into."};
        throw EmptyGroupStackException(emsg);
    }

    std::shared_ptr<GroupToken> commentToken =
        createGroupToken(Token::Type::COMMENT); // Allocate the pointer

    groupStack.push(commentToken);

    while (m_char != '\n') { // Stop at indent
        literal();
    }

    groupStack.pop(); // Pop out parent commentToken

    insertGroupToken(commentToken);
}

std::shared_ptr<GroupToken>
Tokenizer::createGroupToken(const Token::Type &type) const {
    try {
        return std::make_shared<GroupToken>(GroupToken{groupStack.top(), type});
    } catch (const std::bad_alloc &e) {
        ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE,
                          name::TOKENIZER_CREATEGROUPTOKEN,
                          "Failed to allocate GroupToken."};
        throw FailedAllocException(emsg);
    }
}

std::shared_ptr<GroupToken> Tokenizer::createGroupToken(GroupToken &gtok) {
    return std::dynamic_pointer_cast<GroupToken>(gtok.getPtr());
}

std::shared_ptr<SingleToken>
Tokenizer::createSingleToken(const Token::Type &type) const {
    try {
        return std::make_shared<SingleToken>(
            SingleToken{groupStack.top(), type});
    } catch (const std::bad_alloc &e) {
        ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE,
                          name::TOKENIZER_CREATESINGLETOKEN,
                          "Failed to allocate SingleToken."};
        throw FailedAllocException(emsg);
    }
}

std::shared_ptr<SingleToken>
Tokenizer::createSingleToken(const Token::Type &type,
                             std::string &&data) const {
    try {
        return std::make_shared<SingleToken>(
            SingleToken{groupStack.top(), type, std::move(data)});
    } catch (const std::bad_alloc &e) {
        ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE,
                          name::TOKENIZER_CREATESINGLETOKEN_2,
                          "Failed to allocate SingleToken."};
        throw FailedAllocException(emsg);
    }
}

std::shared_ptr<SingleToken> Tokenizer::createSingleToken(SingleToken &stok) {
    return std::dynamic_pointer_cast<SingleToken>(stok.getPtr());
}

void Tokenizer::doubleQuote() {
    insertSingleToken(Token::Type::DOUBLE_QUOTE);
}

const std::shared_ptr<Token> &Tokenizer::getTokens() const {
    if (groupStack.empty()) {
        ErrorMessage emsg_1{name::TOML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_GETTOKENS,
                            "No parent found to insert a Token into."};
        throw EmptyGroupStackException(emsg_1);
    } else if (groupStack.size() > 1) {
        ErrorMessage emsg_2{name::TOML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_GETTOKENS,
                            "Attempted to insert into a GroupToken that was "
                            "not of type pone::TOML::Token::Type::Root."};
        throw RootNotFoundException(emsg_2);
    }

    return groupStack.top(); // Which is always root
}

void Tokenizer::insertGroupToken(const Token::Type &type) {
    if (groupStack.empty()) {
        ErrorMessage emsg_1{name::TOML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_GETTOKENS,
                            "No parent found to insert a Token into."};
        throw EmptyGroupStackException(emsg_1);
    }

    std::shared_ptr<Token> parent = groupStack.top();

    if (parent == nullptr) {
        ErrorMessage emsg_2{name::TOML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_GETTOKENS,
                            "Parent GroupToken is null."};

        throw NullTokenException(emsg_2);
    }

    parent->insert(createGroupToken(type));
}

void Tokenizer::insertGroupToken(const std::shared_ptr<GroupToken> &gtok) {
    if (groupStack.empty()) {
        ErrorMessage emsg_1{name::TOML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_GETTOKENS,
                            "No parent found to insert a Token into."};
        throw EmptyGroupStackException(emsg_1);
    } else if (gtok == nullptr) {
        ErrorMessage emsg_2{name::TOML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_CREATEGROUPTOKEN_2,
                            "Attempted to insert null into parent "
                            "GroupToken."};
        throw NullTokenException(emsg_2);
    }

    std::shared_ptr<Token> parent = groupStack.top();

    if (parent == nullptr) {
        ErrorMessage emsg_3{name::TOML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_GETTOKENS,
                            "Parent GroupToken is null."};
        throw NullTokenException(emsg_3);
    }

    if (gtok != parent) {
        parent->insert(gtok);
    }
}

void Tokenizer::insertSingleToken(const Token::Type &type) {
    if (groupStack.empty()) {
        ErrorMessage emsg_1{name::TOML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_GETTOKENS,
                            "No parent found to insert a Token into."};
        throw EmptyGroupStackException(emsg_1);
    }

    std::shared_ptr<Token> parent = groupStack.top();

    if (parent == nullptr) {
        ErrorMessage emsg_2{name::TOML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_INSERTSINGLETOKEN,
                            "Parent GroupToken is null."};
        throw NullTokenException(emsg_2);
    }

    parent->insert(createSingleToken(type));
}

void Tokenizer::insertSingleToken(const Token::Type &type, std::string &&data) {
    if (groupStack.empty()) {
        ErrorMessage emsg_1{name::TOML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_INSERTSINGLETOKEN_2,
                            "No parent found to insert a Token into."};
        throw EmptyGroupStackException(emsg_1);
    }

    std::shared_ptr<Token> parent = groupStack.top();

    if (parent == nullptr) {
        ErrorMessage emsg_2{name::TOML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_INSERTSINGLETOKEN_2,
                            "Parent GroupToken is null"};
    }

    parent->insert(createSingleToken(type, std::move(data)));
}

void Tokenizer::insertSingleToken(const std::shared_ptr<SingleToken> &stok) {
    if (groupStack.empty()) {
        ErrorMessage emsg_1{name::TOML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_INSERTSINGLETOKEN_3,
                            "No parent to insert Token "
                            "into."};
        throw EmptyGroupStackException(emsg_1);
    }

    std::shared_ptr<Token> parent = groupStack.top();

    if (parent == nullptr) {
        ErrorMessage emsg_2{name::TOML_GLOBAL_NAMESPACE,
                            name::TOKENIZER_INSERTSINGLETOKEN_3,
                            "Parent GroupToken is null."};
        throw NullTokenException(emsg_2);
    }

    parent->insert(stok);
}

void Tokenizer::key() {
    if (groupStack.empty()) {
        ErrorMessage emsg_1{name::TOML_GLOBAL_NAMESPACE, name::TOKENIZER_KEY,
                            "No parent to insert Token into."};
        throw EmptyGroupStackException(emsg_1);
    }

    std::shared_ptr<GroupToken> keyToken = createGroupToken(Token::Type::KEY);

    groupStack.push(keyToken);

    while (m_char != ':') {
        if (m_char == '\n') {
            // Reject the keyToken
            // and release tokens into parent Token

            keyToken->release();
            groupStack.pop(); // Discard the keyToken

            // The key failed, therefore the mapping does
            // throw malformed map exception
            // and have mapping() call catch this

            ErrorMessage emsg_2{name::TOML_GLOBAL_NAMESPACE,
                                name::TOKENIZER_KEY, "Missing ':' operator."};
            throw InvalidKeyException(emsg_2);

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
    insertSingleToken(Token::Type::LEFT_BRACE);
}

void Tokenizer::leftBracket() {
    insertSingleToken(Token::Type::LEFT_BRACKET);
}

void Tokenizer::literal() {
    // TODO: Implement this
}

const char Tokenizer::lookahead() {
    // Looks ahead of the current character from ifstream
    int nextChar = m_ifs.peek();
    if (nextChar == std::char_traits<char>::eof()) {
        m_endOfFile = true;
        ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE,
                          name::TOKENIZER_LOOKAHEAD,
                          "Reached EOF on current filestream."};
        throw EndOfIfstreamException(emsg);
    }

    return static_cast<char>(nextChar);
}

void Tokenizer::mapping() {
    // A mapping consists of a key and token;
    // therefore, the key token will be processed first
    // and along with it, the value.

    while (!isSpace(m_char)) {
        whitespace(); // Consume all whitespace first
    }

    try {
        key();
    } catch (const InvalidMappingException &e) {
    }

    colon(); // Consume colon token
    try {
        next();
    } catch (const EndOfIfstreamException &) {
        return; // Discard mapping
    }

    // FIXME: Mapping should be rejected
    //        if colon does not have ' ' after it.
    if (!isSpace(m_char)) {
        while (!isSpace(m_char)) {
            whitespace(); // Consume any whitespace
        }
    } else {
        ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE, name::TOKENIZER_MAPPING,
                          "Failed to generate a mapping token."};
        throw InvalidMappingException(emsg);
    }

    value();
}

void Tokenizer::newline() {
    insertSingleToken(Token::Type::NEWLINE);
}

void Tokenizer::next() {
    m_ifs.get(m_char);
    if (m_ifs.eof()) {
        m_endOfFile = true;
        ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE, name::TOKENIZER_NEXT,
                          "Reached EOF on current filestream."};
        throw EndOfIfstreamException(emsg);
    }
}

void Tokenizer::numSign() {
    insertSingleToken(Token::Type::NUMSIGN);
}

void Tokenizer::print(std::ostream &out) const {
    std::shared_ptr<Token> root = getTokens(); // returns ptr to root
    std::vector<std::string> indentVector;
    root->print(out, indentVector, "");
}

void Tokenizer::quoted() {
    if (groupStack.empty()) {
        ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE, name::TOKENIZER_QUOTED,
                          "No parent to insert Token into."};
        throw EmptyGroupStackException(emsg);
    }

    std::shared_ptr<GroupToken> quotedToken =
        createGroupToken(Token::Type::QUOTED);

    groupStack.push(quotedToken);

    if (m_char == '"') {
        doubleQuote();

        while (m_char != '"') {
            literal();
        }

        doubleQuote();           // Consume ending quote
    } else if (m_char == '\'') { // This is single-quoted
        singleQuote();

        while (m_char != '\'') {
            literal();
        }

        singleQuote(); // Consume ending quote
    } else {
        return;
    }

    groupStack.pop();
}

void Tokenizer::rightBrace() {
    insertSingleToken(Token::Type::RIGHT_BRACE);
}

void Tokenizer::rightBracket() {
    insertSingleToken(Token::Type::RIGHT_BRACKET);
}

void Tokenizer::singleQuote() {
    insertSingleToken(Token::Type::SINGLE_QUOTE);
}

void Tokenizer::tokenize() {
    try {
        next(); // Start with first token
    } catch (const EndOfIfstreamException &) {
        return; // Means empty file
    }

    while (!m_endOfFile) {
        mapping();
        sequence();
        if (m_char == '#') { // Must be symbol
            comment();       // This is to check for comments
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
        createGroupToken(Token::Type::VALUE);
    groupStack.push(valueToken);

    if (m_char == '-') {
        sequence();
    } else if (isQuote(m_char)) {
        quoted();
        return; // A value if quoted must end
    } else {
        while (m_char == '\n') {
            if (m_char == '#') {
                sym(); // Directly check for '#'
            } else if (isQuote(m_char)) {
                // Throw as this should not be in here
                ErrorMessage emsg{name::TOML_GLOBAL_NAMESPACE,
                                  name::TOKENIZER_VAL,
                                  "Quoted value must be wrapped in a single "
                                  "set of quotations."};
                throw InvalidValueException(emsg);
            }
            mapping(); // check mapping first
            literal();
        }
    }

    groupStack.pop(); // valueToken

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

} // namespace pone::TOML

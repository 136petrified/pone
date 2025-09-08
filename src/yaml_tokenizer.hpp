/*   Created:  07-23-2025
 *   Modified: 09-08-2025
 */

#ifndef PONE_YAML_TOKENIZER_HPP
#define PONE_YAML_TOKENIZER_HPP

#include <array>
#include <fstream>
#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "yaml_utils.hpp"

namespace YAML {
class Token {
   public:
    enum class Type {
        Backslash,
        Colon,
        Comma,
        Comment,
        Dash,
        DoubleQuote,
        DoubleQuotedKey,
        DoubleQuotedValue,
        Key,
        LeftBrace,
        LeftBracket,
        Newline,
        None,
        NumSign,
        RightBrace,
        RightBracket,
        Scalar,
        SingleQuote,
        SingleQuotedKey,
        SingleQuotedValue,
        Space,
        Symbol,
        Tab,
        Value,
    };

    enum class Class {
        // This is a "type" to differentiate derived classes
        Group,
        Single
    };

    static const int ALL_TOKEN_SYM_TYPES_SIZE = 24;
    const std::array<Type, ALL_TOKEN_SYM_TYPES_SIZE> ALL_TOKEN_SYM_TYPES = {
        Type::Backslash,
        Type::Colon,
        Type::Comma,
        Type::Comment,
        Type::Dash,
        Type::DoubleQuote,
        Type::DoubleQuotedKey,  // TODO: Find way to separate this
        Type::DoubleQuotedValue,
        Type::Key,
        Type::LeftBracket,
        Type::LeftBrace,
        Type::Newline,
        Type::None,
        Type::NumSign,
        Type::RightBrace,
        Type::RightBracket,
        Type::Scalar,
        Type::SingleQuote,
        Type::SingleQuotedKey,
        Type::SingleQuotedValue,
        Type::Space,
        Type::Symbol,
        Type::Tab,
        Type::Value};

    Token();
    virtual ~Token() = 0;

    // Start of basic Token functions
    virtual std::unique_ptr<Token> clone() const = 0;
    virtual Class getClass() const = 0;
    virtual Type getType() const = 0;
    virtual void setType(const Type &type) = 0;
    // End of basic Token functions

    // Start of basic SingleToken functions
    virtual std::string &&getData();
    virtual void setData(const std::string &data);
    // End of basic SingleToken functions

    // Start of basic GroupToken functions
    virtual void clearTokenGroup();
    virtual std::vector<std::unique_ptr<Token>> getTokenGroup() const;
    virtual void insertToTokenGroup(std::unique_ptr<Token> &&token);
    virtual bool isTokenGroupEmpty() const;
    virtual size_t sizeOfTokenGroup() const;
    // End of basic GroupToken functions
};

class SingleToken : public Token {
   public:
    SingleToken();
    SingleToken(const Token::Type &type);
    SingleToken(const Token::Type &type, const std::string &data);
    SingleToken(const Token::Type &type, std::string &&data);
    SingleToken(const SingleToken &other);
    SingleToken &operator=(const SingleToken &other);
    // This will move the data out of m_data! Only call once
    std::string &&getData() override;
    void setData(const std::string &data) override;
    ~SingleToken();

    // Pure virtual functions from Token
    std::unique_ptr<Token> clone() const override;
    Token::Class getClass() const override;
    Token::Type getType() const override;
    void setType(const Token::Type &type) override;

   private:
    Token::Class m_class;
    std::string m_data;
    Token::Type m_type;
};

class GroupToken : public Token {
    // NOTE: This allows for a Token to be made up of Tokens
   public:
    GroupToken();
    GroupToken(const Token::Type &type);
    GroupToken(const GroupToken &other);
    GroupToken(GroupToken &&other);
    GroupToken &operator=(const GroupToken &other);
    GroupToken &operator=(GroupToken &&other);
    void clearTokenGroup() override;
    std::vector<std::unique_ptr<Token>> getTokenGroup() const override;
    void insertToTokenGroup(std::unique_ptr<Token> &&token) override;
    bool isTokenGroupEmpty() const override;
    size_t sizeOfTokenGroup() const override;
    ~GroupToken();

    // Pure virtual functions from Token
    std::unique_ptr<Token> clone() const override;
    Token::Class getClass() const override;
    Token::Type getType() const override;
    void setType(const Token::Type &type) override;

   private:
    Token::Class m_class;
    std::vector<std::unique_ptr<Token>> m_tokenGroup;
    size_t m_tokenGroupSize;
    Token::Type m_type;
};

class Tokenizer {
   public:
    Tokenizer();
    Tokenizer(const std::string &file_name);
    std::vector<std::unique_ptr<Token>> getTokens() const;
    void tokenize();
    ~Tokenizer();

   protected:
    void backslash();
    void backslash(GroupToken &gtok);
    void clearBuf();
    void colon();
    void colon(GroupToken &gtok);
    void comma();
    void comma(GroupToken &gtok);
    void comment();
    // TODO: Change type to derived
    std::unique_ptr<Token> createGroupToken(const Token::Type &tokenType) const;
    std::unique_ptr<Token> createSingleToken(
        const Token::Type &tokenType) const;
    std::unique_ptr<Token> createSingleToken(const Token::Type &tokenType,
                                             std::string &&data) const;
    void dash();
    void dash(GroupToken &gtok);
    void doubleQuote();
    void doubleQuote(GroupToken &gtok);
    void doubleQuotedKey(GroupToken &gtok);
    void doubleQuotedValue(GroupToken &gtok);
    void insertGroupTokenToGroupToken(GroupToken &gtok,
                                      const Token::Type &tokenType);
    void insertSingleTokenToGroupToken(GroupToken &gtok,
                                       const Token::Type &tokenType);
    void key();
    void key(GroupToken &gtok);
    void leftBrace();
    void leftBrace(GroupToken &gtok);
    void leftBracket();
    void leftBracket(GroupToken &gtok);
    const char lookahead();
    void mapping();
    void newline();
    void newline(GroupToken &gtok);
    void next();
    void numSign();
    void numSign(GroupToken &gtok);
    void otherSymbols();
    void otherSymbols(GroupToken &gtok);
    void rightBrace();
    void rightBrace(GroupToken &gtok);
    void rightBracket();
    void rightBracket(GroupToken &gtok);
    void scalar();
    void scalar(GroupToken &gtok);
    void singleQuote();
    void singleQuote(GroupToken &gtok);
    void singleQuotedKey();
    void singleQuotedKey(GroupToken &gtok);
    void singleQuotedValue();
    void singleQuotedValue(GroupToken &gtok);
    void space();
    void space(GroupToken &gtok);
    // This is a symbol "multiplexer"
    void sym();
    void sym(GroupToken &gtok);
    void tab();
    void tab(GroupToken &gtok);
    void value();
    void value(GroupToken &gtok);
    // This is a whitespace "multiplexer"
    void whitespace();
    void whitespace(GroupToken &gtok);

   private:
    std::string m_file_name;
    std::ifstream m_ifs;

    std::vector<std::unique_ptr<Token>> m_tokens;
    size_t m_tokensSize;

    std::string m_buf;
    char m_char;

    std::stack<GroupToken> groupTokenStack;
    bool m_endOfFile;
};
}  // namespace YAML

#endif  // PONE_YAML_TOKENIZER_HPP

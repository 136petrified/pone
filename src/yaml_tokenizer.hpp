/*   Created:  07-23-2025
 *   Modified: 08-30-2025
 */

#ifndef PONE_YAML_TOKENIZER_HPP
#define PONE_YAML_TOKENIZER_HPP

#include <array>
#include <fstream>
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
        NumSign,
        RightBrace,
        RightBracket,
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

    static const int ALL_TOKEN_SYM_TYPES_SIZE = 22;
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
        Type::NumSign,
        Type::RightBrace,
        Type::RightBracket,
        Type::SingleQuote,
        Type::SingleQuotedKey,
        Type::SingleQuotedValue,
        Type::Space,
        Type::Symbol,
        Type::Tab,
        Type::Value};

    using TokenGroup = std::vector<Token>;

   protected:
    Token();
    Token(const Type &type);
    Token(const Type &type, std::string &&data);

    // Start of basic Token functions
    virtual Class getClass() const = 0;
    virtual Type getType() const = 0;
    virtual void setType(const Type &type) = 0;
    // End of basic Token functions

    // Start of SingleToken functions
    // This will move the data out of m_data! Only call once
    virtual std::string &&getData();
    virtual void setData(const std::string &data);
    // End of SingleToken functions

    // Start of GroupToken functions
    virtual void clearTokenGroup();
    virtual void insertToTokenGroup(const Token &token);
    virtual bool isTokenGroupEmpty() const;
    virtual size_t sizeOfTokenGroup() const;
    // End of GroupToken functions

    virtual ~Token() = 0;
};

class SingleToken : public Token {
   public:
    SingleToken();
    // This will move the data out of m_data! Only call once
    std::string &&getData() override;
    void setData(const std::string &data) override;
    ~SingleToken();

    // Pure virtual functions from Token
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
    void clearTokenGroup() override;
    void insertToTokenGroup(const Token &token) override;
    bool isTokenGroupEmpty() const override;
    size_t sizeOfTokenGroup() const override;
    ~GroupToken();

    // Pure virtual functions from Token
    Token::Class getClass() const override;
    Token::Type getType() const override;
    void setType(const Token::Type &type) override;

   private:
    Token::Class m_class;
    TokenGroup m_tokenGroup;
    size_t m_tokenGroupSize;
    Token::Type m_type;
};

class Tokenizer {
   public:
    Tokenizer();
    Tokenizer(const std::string &file_name);
    std::vector<Token> getTokens() const;
    void tokenize();
    ~Tokenizer();

   protected:
    void backslash();
    Token &clearBuf(const Token::Type &tokenType);
    void colon();
    void comma();
    void comment();
    void dash();
    void doubleQuote();
    void doubleQuotedKey();
    void doubleQuotedValue();
    void key();
    void leftBrace();
    void leftBracket();
    const char lookahead();
    void rightBrace();
    void rightBracket();
    void newline();
    void next();
    void numSign();
    void otherSymbols();
    void scalar();
    void singleQuote();
    void singleQuotedKey();
    void singleQuotedValue();
    void space();
    void sym();
    void tab();
    void toggleEscape();
    void tokenizeSpecialChar(
        const Token::Type &tokenType);  // Tokenize a single character
    void whitespace();

   private:
    std::string m_file_name;
    std::ifstream m_ifs;
    std::vector<Token> m_tokens;
    std::string m_buf;
    char m_char;
    bool m_endOfFile;
};
}  // namespace YAML

#endif  // PONE_YAML_TOKENIZER_HPP

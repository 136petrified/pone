/*   Created:  07-23-2025
 *   Modified: 08-24-2025
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

    Token();
    Token(const Type &type, std::string &&data);
    Type m_type;
    std::string &&
    getData();  // This will move the data out of m_data! Only call once
    bool inQuotes() const;
    static bool isSymbol(const Token &token);
    void setData(const std::string &data);

   private:
    std::string m_data;
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

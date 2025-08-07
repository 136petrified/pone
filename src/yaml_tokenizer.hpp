/*   Created:  07-23-2025
 *   Modified: 08-07-2025
 */

#ifndef PONE_YAML_TOKENIZER_HPP
#define PONE_YAML_TOKENIZER_HPP

#include <fstream>
#include <string>
#include <vector>

#include "yaml_utils.hpp"

namespace YAML {
enum class TokenType {
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
    END
};

constexpr TokenType ALL_TOKEN_SYM_TYPES[] = {TokenType::Backslash,
                                             TokenType::Colon,
                                             TokenType::Comma,
                                             TokenType::Comment,
                                             TokenType::Dash,
                                             TokenType::DoubleQuote,
                                             TokenType::DoubleQuotedKey,
                                             TokenType::DoubleQuotedValue,
                                             TokenType::Key,
                                             TokenType::LeftBracket,
                                             TokenType::LeftBrace,
                                             TokenType::Newline,
                                             TokenType::NumSign,
                                             TokenType::RightBrace,
                                             TokenType::RightBracket,
                                             TokenType::SingleQuote,
                                             TokenType::SingleQuotedKey,
                                             TokenType::SingleQuotedValue,
                                             TokenType::Space,
                                             TokenType::Symbol,
                                             TokenType::Tab,
                                             TokenType::Value};
constexpr int ALL_TOKEN_SYM_TYPES_SIZE = 22;

class Token {
   public:
    Token();
    Token(const TokenType &type, std::string &&data);
    TokenType m_type;
    std::string &&getData();  // This will move the data out! Only call once
    bool inQuotes() const;
    static bool isSymbol(const Token &token);
    void setData(const std::string &data);

   private:
    std::string m_data;
    bool m_isEscaped;
};

class Tokenizer {
   public:
    Tokenizer();
    Tokenizer(const std::string &file_name);
    void backslash(std::ifstream &ifs);
    Token &clearBuf(const TokenType &tokenType);
    void colon(std::ifstream &ifs);
    void comma(std::ifstream &ifs);
    void comment(std::ifstream &ifs);
    void dash(std::ifstream &ifs);
    void doubleQuote(std::ifstream &ifs);
    void doubleQuotedKey(std::ifstream &ifs);
    void doubleQuotedValue(std::ifstream &ifs);
    std::vector<Token> getTokens() const;
    void key(std::ifstream &ifs);
    void leftBrace(std::ifstream &ifs);
    void leftBracket(std::ifstream &ifs);
    const char lookahead(std::ifstream &ifs);
    void rightBrace(std::ifstream &ifs);
    void rightBracket(std::ifstream &ifs);
    void next(std::ifstream &ifs);
    void newline(std::ifstream &ifs);
    void numSign(std::ifstream &ifs);
    void otherSymbols(std::ifstream &ifs);
    void scalar(std::ifstream &ifs);
    void singleQuote(std::ifstream &ifs);
    void singleQuotedKey(std::ifstream &ifs);
    void singleQuotedValue(std::ifstream &ifs);
    void space(std::ifstream &ifs);
    void sym(std::ifstream &ifs);
    void tab(std::ifstream &ifs);
    void tokenize();
    void tokenizeSpecialChar(
        std::ifstream &ifs,
        const TokenType &tokenType);  // Tokenize a single character
    void whitespace(std::ifstream &ifs);
    ~Tokenizer();

   private:
    std::string m_file_name;
    std::vector<Token> m_tokens;
    std::string m_buf;
    char m_char;
    bool m_endOfFile;
};
}  // namespace YAML

#endif  // PONE_YAML_TOKENIZER_HPP

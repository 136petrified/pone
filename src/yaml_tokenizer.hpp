/*   Created:  07-23-2025
 *   Modified: 08-06-2025
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
    Key,
    LeftSquareBracket,
    Newline,
    NumSign,
    RightSquareBracket,
    SingleQuote,
    Space,
    Symbol,
    Tab,
    Value
};

constexpr TokenType ALL_TOKEN_SYM_TYPES[] = {TokenType::Backslash,
                                             TokenType::Colon,
                                             TokenType::Comma,
                                             TokenType::Comment,
                                             TokenType::Dash,
                                             TokenType::DoubleQuote,
                                             TokenType::Key,
                                             TokenType::LeftSquareBracket,
                                             TokenType::Newline,
                                             TokenType::NumSign,
                                             TokenType::RightSquareBracket,
                                             TokenType::SingleQuote,
                                             TokenType::Space,
                                             TokenType::Symbol,
                                             TokenType::Tab,
                                             TokenType::Value};
constexpr int ALL_TOKEN_SYM_TYPES_SIZE = 16;

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
    bool m_inQuotes;
    bool m_isEscaped;
};

class Tokenizer {
   public:
    Tokenizer();
    Tokenizer(const std::string &file_name);
    Token &clearBuf(const TokenType &tokenType);
    void comment(std::ifstream &ifs);
    std::vector<Token> getTokens() const;
    const char lookahead(std::ifstream &ifs);
    void next(std::ifstream &ifs);
    void scalar(std::ifstream &ifs);
    void sym(std::ifstream &ifs);
    void whitespace(std::ifstream &ifs);
    void tokenize();
    void toggleQuoted();
    ~Tokenizer();

   private:
    std::string m_file_name;
    std::vector<Token> m_tokens;
    std::string m_buf;
    char m_char;
    bool m_endOfFile;
    bool m_isQuoted;
};
}  // namespace YAML

#endif  // PONE_YAML_TOKENIZER_HPP

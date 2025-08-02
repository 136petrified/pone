/*   Created:  07-23-2025
 *   Modified: 08-01-2025
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

constexpr TokenType allTokenSymTypes[] = {TokenType::Backslash,
                                          TokenType::Colon,
                                          TokenType::Comma,
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
};

class Tokenizer {
   public:
    Tokenizer();
    Tokenizer(const std::string &file_name);
    void clearBuf(const TokenType &tokenType);
    std::vector<Token> getTokens() const;
    const char lookahead(std::ifstream &ifs) const;
    void next(std::ifstream &ifs);
    void scalar(std::ifstream &ifs);
    void sym(std::ifstream &ifs);
    void whitespace(std::ifstream &ifs);
    void tokenize();
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

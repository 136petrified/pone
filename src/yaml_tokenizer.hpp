/*   Created:  07-23-2025
 *   Modified: 07-24-2025
 */

#ifndef PONE_YAML_TOKENIZER_HPP
#define PONE_YAML_TOKENIZER_HPP

#include <string>
#include <vector>

#include "yaml_utils.hpp"

namespace YAML {
enum class TokenType { Scalar, Symbol };
class Token {
   public:
    Token(const TokenType &type, std::string &&data);
    TokenType m_type;
    std::string &&getData();  // This will move the data out! Only call once
    void setData(const std::string &data);

   private:
    std::string m_data;
};

class Tokenizer {
   public:
    Tokenizer();
    Tokenizer(const std::string &file_name);
    void clearBuf(const TokenType &tokenType);
    std::vector<Token> getTokens() const;
    void next(std::ifstream &ifs);
    void scalar(std::ifstream &ifs);
    void sym(std::ifstream &ifs);
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

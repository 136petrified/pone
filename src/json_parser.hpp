/*   Created:  07-17-2025
 *   Modified: 07-21-2025
 */

#ifndef PONE_JSON_PARSER_HPP
#define PONE_JSON_PARSER_HPP

#include <stack>

#include "json_tokenizer.hpp"

namespace JSON {
class Parser {
   public:
    Parser();
    Parser(const Tokenizer &tokenizer, const std::string &file_name);
    void curlyBracket();
    void expr();
    void key();
    void next();
    void paren();
    void parse();
    void squareBracket();
    void symbol();
    void value();

    bool isAlnum(std::string &s);
    bool isAlpha(std::string &s);
    bool isDigit(std::string &s);
    bool isSymbol(std::string &s);
    ~Parser();

   private:
    bool m_endOfTokens;
    int m_tokenIndex;
    std::string m_currentToken;
    std::vector<std::string> m_tokens;
    std::stack<std::string> m_parenStack;
    std::string m_file_name;
};
}  // namespace JSON

#endif  // PONE_JSON_PARSER_HPP

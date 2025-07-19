/*   Created:  07-17-2025
 *   Modified: 07-19-2025
 */

#ifndef PONE_JSON_PARSER_HPP
#define PONE_JSON_PARSER_HPP

#include <stack>

#include "json_tokenizer.hpp"

namespace JSON {
class Parser {
   public:
    Parser();
    Parser(const Tokenizer &tokenizer);
    void curlyBracket();
    void expr();
    void next();
    void paren();
    void parse();
    void squareBracket();
    void symbol();

    static bool isAlnum(std::string &s);
    static bool isAlpha(std::string &s);
    static bool isDigit(std::string &s);
    static bool isSymbol(std::string &s);
    ~Parser();

   private:
    bool m_endOfTokens;
    int m_tokenIndex;
    std::string m_currentToken;
    std::vector<std::string> m_tokens;
    std::stack<std::string> m_parenStack;
};
}  // namespace JSON

#endif  // PONE_JSON_PARSER_HPP

/*   Created:  07-17-2025
 *   Modified: 07-21-2025
 */

#ifndef PONE_JSON_TOKENIZER_HPP
#define PONE_JSON_TOKENIZER_HPP

#include <string>
#include <vector>

namespace JSON {
class Tokenizer {
   public:
    Tokenizer();
    Tokenizer(const std::string &file_name);
    bool isAlnum(std::string &s);
    bool isAlpha(std::string &s);
    bool isDigit(std::string &s);
    bool isSymbol(std::string &s);
    std::vector<std::string> getTokens() const;
    void tokenize();
    ~Tokenizer();

   private:
    std::vector<std::string> m_tokens;
    std::string m_file_name;
};
}  // namespace JSON

#endif  // PONE_JSON_TOKENIZER_HPP

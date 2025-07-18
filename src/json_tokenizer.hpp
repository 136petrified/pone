/*   Created:  07-17-2025
 *   Modified: 07-17-2025
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
    void tokenize();
    std::vector<std::string> getTokens() const;
    ~Tokenizer();

   private:
    std::vector<std::string> m_tokens;
};
}  // namespace JSON

#endif  // PONE_JSON_TOKENIZER_HPP

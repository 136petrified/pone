/*   Created:  07-23-2025
 *   Modified: 07-24-2025
 */

#ifndef PONE_YAML_TOKENIZER_HPP
#define PONE_YAML_TOKENIZER_HPP

#include <string>
#include <vector>

#include "yaml_utils.hpp"

namespace YAML {
class Tokenizer {
   public:
    Tokenizer();
    Tokenizer(const std::string &file_name);
    void clearToken();
    std::vector<std::string> getTokens() const;
    void next(std::ifstream &ifs);
    void scalar(std::ifstream &ifs);
    void sym(std::ifstream &ifs);
    void tokenize();
    ~Tokenizer();

   private:
    std::string m_file_name;
    std::vector<std::string> m_tokens;
    std::string m_buf;
    char m_char;
};
}  // namespace YAML

#endif  // PONE_YAML_TOKENIZER_HPP

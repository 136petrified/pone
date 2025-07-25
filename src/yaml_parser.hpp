/*   Created:  07-23-2025
 *   Modified: 07-24-2025
 */

#include <string>
#include <vector>

#include "yaml_tokenizer.hpp"

namespace YAML {
class Parser {
   public:
    Parser(const Tokenizer &tokenizer, const std::string &file_name);
    void parse();
    void scalar();
    void symbol();
    ~Parser();

   private:
    int m_tokenIndex;
    std::vector<Token> m_tokens;
};
}  // namespace YAML

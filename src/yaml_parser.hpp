/*   Created:  07-23-2025
 *   Modified: 08-02-2025
 */

#include <string>
#include <vector>

#include "yaml_tokenizer.hpp"

namespace YAML {
constexpr std::string PONE_RESERVED_KEYS[] = {
    "board", "boards", "cursor", "gates", "gate", "tile", "tiles",
};
constexpr int PONE_RESERVED_KEYS_SIZE = 7;

class Parser {
   public:
    Parser();
    Parser(const Tokenizer &tokenizer, const std::string &file_name);
    void colon();
    void comment();
    void key();
    void list();
    void newline();
    void next();
    void parse();
    void sequence();
    void space();
    void symbol();
    void value();
    void tab();  // This will error; tabs not allowed in YAML
    ~Parser();

   private:
    int m_tokenIndex;
    std::vector<Token> m_tokens;
    Token m_token;
    bool m_endOfFile;
    std::string m_file_name;
};
}  // namespace YAML

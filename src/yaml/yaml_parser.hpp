/*   Created:  07-23-2025
 *   Modified: 01-05-2026
 */

#pragma once

#include <string>
#include <vector>
#include "yaml_tokenizer.hpp"

namespace pone::YAML {
constexpr std::string PONE_RESERVED_KEYS[] = {
    "board", "boards", "cursor", "gates", "gate", "tile", "tiles",
};
constexpr int PONE_RESERVED_KEYS_SIZE = 7;

class Parser {
    int m_tokenIndex;
    std::vector<std::shared_ptr<Token>> m_tokens;
    bool m_eof;
    std::string m_fileName;

   public:
    Parser();
    Parser(const Tokenizer &tokenizer, const std::string &fileName);
    ~Parser();
};

}  // namespace pone::YAML

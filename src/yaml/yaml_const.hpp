/*   Created:  10-21-2025
 *   Modified: 10-21-2025
 */

#include <string_view>

namespace YAML {

// YAML Tokenizer constants
// +--------------------------------+

inline constexpr std::string_view TOKEN_TOKEN_1 =
    "YAML::Token::Token(const std::shared_ptr<Token>, const std::string &, "
    "const Token::Class &)";
inline constexpr std::string_view TOKEN_GETCLASS = "YAML::Token::getClass()";
inline constexpr std::string_view TOKEN_GETDEPTH = "YAML::Token::getDepth()";

}  // namespace YAML

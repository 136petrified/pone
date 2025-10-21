/*   Created:  10-21-2025
 *   Modified: 10-21-2025
 */

#include <string_view>

namespace YAML {

inline constexpr std::string_view YAML_GLOBAL_NAMESPACE = "pone::YAML::";

// YAML Tokenizer constants
// +--------------------------------+

inline constexpr std::string_view TOKEN_NAMESPACE       = "Token::";
inline constexpr std::string_view TOKEN_TOKEN_1 =
    "Token(const std::shared_ptr<Token>, const std::string &, "
    "const Token::Class &)";
inline constexpr std::string_view TOKEN_TOKEN_2 =
    "Token(const std::shared_ptr<Token>, const std::string &, const "
    "Token::Type &";
inline constexpr std::string_view TOKEN_GETCLASS = "getClass()";
inline constexpr std::string_view TOKEN_GETDEPTH = "getDepth()";

}  // namespace YAML

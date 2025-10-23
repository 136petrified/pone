/*   Created:  10-21-2025
 *   Modified: 10-22-2025
 */

#include <string_view>

namespace YAML {

// +--------------------------------+
// YAML global constants            +
// +--------------------------------+

inline constexpr std::string_view YAML_GLOBAL_NAMESPACE = "pone::YAML::";

// +--------------------------------+
// YAML Tokenizer constants         +
// +--------------------------------+

// Start of YAML::Token constants

inline constexpr std::string_view TOKEN_NAMESPACE       = "Token::";
inline constexpr std::string_view TOKEN_TOKEN_1 =
    "Token(const std::shared_ptr<Token>, const std::string &, "
    "const Token::Class &)";
inline constexpr std::string_view TOKEN_TOKEN_2 =
    "Token(const std::shared_ptr<Token>, const std::string &, const "
    "Token::Type &";
inline constexpr std::string_view TOKEN_GETCLASS  = "getClass()";
inline constexpr std::string_view TOKEN_GETDEPTH  = "getDepth()";
inline constexpr std::string_view TOKEN_GETNAME   = "getName()";
inline constexpr std::string_view TOKEN_GETPARENT = "getParent()";
inline constexpr std::string_view TOKEN_GETTYPE   = "getType()";
inline constexpr std::string_view TOKEN_PRINTENTRY =
    "printEntry(std::ostream&, std::vector<std::string>&, const std::string&)";
inline constexpr std::string_view TOKEN_SETDEPTH = "setDepth()";
inline constexpr std::string_view TOKEN_SETPARENT =
    "setParent(const std::shared_ptr<Token>&)";
inline constexpr std::string_view TOKEN_CLONE = "clone()";

// End of YAML::Token constants

// +--------------------------------+
// YAML SingleToken constants       +
// +--------------------------------+

// Start of YAML::SingleToken constants

}  // namespace YAML

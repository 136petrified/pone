/*   Created:  10-21-2025
 *   Modified: 10-23-2025
 */

#pragma once

#include <string_view>

namespace YAML::name {

// +--------------------------------+
// YAML global constants            +
// +--------------------------------+

inline constexpr std::string_view YAML_GLOBAL_NAMESPACE = "pone::YAML::";
inline constexpr std::string_view ERR_FILE              = "./errlog.txt";
inline constexpr std::string_view NO_ERR_LOCATION       = "<unknown>";

// +--------------------------------+
// YAML Tokenizer constants         +
// +--------------------------------+

// Start of YAML::Token constants

inline constexpr std::string_view TOKEN_NAMESPACE = "Token::";
inline constexpr std::string_view STOK_NAMESPACE  = "SingleToken::";
inline constexpr std::string_view GTOK_NAMESPACE  = "GroupToken::";

inline constexpr std::string_view TOKEN_TOKEN_1 =
    "Token(const std::shared_ptr<pone::YAML::Token>, const std::string &, "
    "const Token::Class &)";
inline constexpr std::string_view TOKEN_TOKEN_2 =
    "Token(const std::shared_ptr<pone::YAML::Token>, const std::string &, "
    "const "
    "pone::YAML::Token::Type &";
inline constexpr std::string_view TOKEN_GETCLASS  = "getClass()";
inline constexpr std::string_view TOKEN_GETDEPTH  = "getDepth()";
inline constexpr std::string_view TOKEN_GETNAME   = "getName()";
inline constexpr std::string_view TOKEN_GETPARENT = "getParent()";
inline constexpr std::string_view TOKEN_GETTYPE   = "getType()";
inline constexpr std::string_view TOKEN_PRINTENTRY =
    "printEntry(std::ostream&, std::vector<std::string>&, const std::string&)";
inline constexpr std::string_view TOKEN_SETDEPTH = "setDepth()";
inline constexpr std::string_view TOKEN_SETNAME  = "setName()";
inline constexpr std::string_view TOKEN_SETTYPE =
    "setType(const pone::YAML::Token::Type&)";
inline constexpr std::string_view TOKEN_CLONE =
    "clone(std::shared_ptr<pone::YAML::Token>)";
inline constexpr std::string_view TOKEN_GETPTR = "getPtr()";
inline constexpr std::string_view TOKEN_PRINT =
    "print(const std::ostream&, std::vector<std::string>&, const std::string&)";
inline constexpr std::string_view TOKEN_SETPARENT =
    "setParent(const std::shared_ptr<pone::YAML::Token>&)";

// Start of YAML::SingleToken constants

inline constexpr std::string_view TOKEN_GETDATA = "getData()";
inline constexpr std::string_view TOKEN_SETDATA = "setData(const std::string&)";

// End of YAML::SingleToken constants

// Start of YAML::GroupToken constants

inline constexpr std::string_view TOKEN_CLEAR     = "clear()";
inline constexpr std::string_view TOKEN_COPY      = "copy()";
inline constexpr std::string_view TOKEN_GETTOKENS = "getTokens()";
inline constexpr std::string_view TOKEN_INSERT =
    "insert(std::shared_ptr<pone::YAML::Token>)";
inline constexpr std::string_view TOKEN_EMPTY   = "empty()";
inline constexpr std::string_view TOKEN_RELEASE = "release()";
inline constexpr std::string_view TOKEN_SIZE    = "size()";

// End of YAML::GroupToken constants

// End of YAML::Token constants

}  // namespace YAML::name

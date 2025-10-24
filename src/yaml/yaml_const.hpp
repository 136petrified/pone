/*   Created:  10-21-2025
 *   Modified: 10-24-2025
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

inline constexpr std::string_view TOKEN_TOKEN_1 =
    "Token::Token(const std::shared_ptr<pone::YAML::Token>, const std::string "
    "&, "
    "const Token::Class &)";
inline constexpr std::string_view TOKEN_TOKEN_2 =
    "Token::Token(const std::shared_ptr<pone::YAML::Token>, const std::string "
    "&, "
    "const "
    "pone::YAML::Token::Type &";
inline constexpr std::string_view TOKEN_GETCLASS  = "Token::getClass()";
inline constexpr std::string_view TOKEN_GETDEPTH  = "Token::getDepth()";
inline constexpr std::string_view TOKEN_GETNAME   = "Token::getName()";
inline constexpr std::string_view TOKEN_GETPARENT = "Token::getParent()";
inline constexpr std::string_view TOKEN_GETTYPE   = "Token::getType()";
inline constexpr std::string_view TOKEN_PRINTENTRY =
    "Token::printEntry(std::ostream&, std::vector<std::string>&, const "
    "std::string&)";
inline constexpr std::string_view TOKEN_SETDEPTH = "Token::setDepth()";
inline constexpr std::string_view TOKEN_SETNAME  = "Token::setName()";
inline constexpr std::string_view TOKEN_SETTYPE =
    "Token::setType(const pone::YAML::Token::Type&)";
inline constexpr std::string_view TOKEN_CLONE =
    "Token::clone(std::shared_ptr<pone::YAML::Token>)";
inline constexpr std::string_view TOKEN_GETPTR = "Token::getPtr()";
inline constexpr std::string_view TOKEN_PRINT =
    "Token::print(const std::ostream&, std::vector<std::string>&, const "
    "std::string&)";
inline constexpr std::string_view TOKEN_SETPARENT =
    "Token::setParent(const std::shared_ptr<pone::YAML::Token>&)";

// Start of YAML::SingleToken constants

inline constexpr std::string_view TOKEN_GETDATA = "Token::getData()";
inline constexpr std::string_view TOKEN_SETDATA =
    "Token::setData(const std::string&)";
inline constexpr std::string_view STOK_GETDATA = "SingleToken::getData()";
inline constexpr std::string_view STOK_SETDATA = "SingleToken::setData()";

// End of YAML::SingleToken constants

// Start of YAML::GroupToken constants

inline constexpr std::string_view TOKEN_CLEAR     = "Token::clear()";
inline constexpr std::string_view TOKEN_COPY      = "Token::copy()";
inline constexpr std::string_view TOKEN_GETTOKENS = "Token::getTokens()";
inline constexpr std::string_view TOKEN_INSERT =
    "Token::insert(std::shared_ptr<pone::YAML::Token>)";
inline constexpr std::string_view TOKEN_EMPTY    = "Token::empty()";
inline constexpr std::string_view TOKEN_RELEASE  = "Token::release()";
inline constexpr std::string_view TOKEN_SIZE     = "Token::size()";
inline constexpr std::string_view GTOK_CLEAR     = "GroupToken::clear()";
inline constexpr std::string_view GTOK_COPY      = "GroupToken::copy()";
inline constexpr std::string_view GTOK_GETTOKENS = "GroupToken::getTokens()";
inline constexpr std::string_view GTOK_INSERT =
    "GroupToken::insert(std::shared_ptr<pone::YAML::Token>)";
inline constexpr std::string_view GTOK_EMPTY   = "GroupToken::empty()";
inline constexpr std::string_view GTOK_RELEASE = "GroupToken::release()";
inline constexpr std::string_view GTOK_SIZE    = "GroupToken::size()";

// End of YAML::GroupToken constants

// End of YAML::Token constants

// Start of YAML::Tokenizer constants

inline constexpr std::string_view TOKENIZER_TOKENIZER =
    "Tokenizer::Tokenizer()";
inline constexpr std::string_view TOKENIZER_TOKENIZER_2 =
    "Tokenizer::Tokenizer(const std::string&)";
inline constexpr std::string_view TOKENIZER_SIZE = "Tokenizer::size()";
inline constexpr std::string_view TOKENIZER_GETTOKENS =
    "Tokenizer::getTokens()";
inline constexpr std::string_view TOKENIZER_TOKENIZE = "Tokenizer::tokenize()";
inline constexpr std::string_view TOKENIZER_DTOKENIZER =
    "Tokenizer::~Tokenizer()";
inline constexpr std::string_view TOKENIZER_BACKSLASH =
    "Tokenizer::backslash()";
inline constexpr std::string_view TOKENIZER_CLEARBUF = "Tokenizer::clearBuf()";
inline constexpr std::string_view TOKENIZER_COLON    = "Tokenizer::colon()";
inline constexpr std::string_view TOKENIZER_COMMA    = "Tokenizer::comma()";
inline constexpr std::string_view TOKENIZER_COMMENT  = "Tokenizer::comment()";
inline constexpr std::string_view TOKENIZER_CREATEGROUPTOKEN =
    "Tokenizer::createGroupToken(const pone::YAML::Token::Type&)";
inline constexpr std::string_view TOKENIZER_CREATEGROUPTOKEN_2 =
    "Tokenizer::createGroupToken(pone::YAML::GroupToken&)";
inline constexpr std::string_view TOKENIZER_CREATESINGLETOKEN =
    "Tokenizer::createSingleToken(const pone::YAML::Token::Type&)";
inline constexpr std::string_view TOKENIZER_CREATESINGLETOKEN_2 =
    "Tokenizer::createSingleToken(const pone::YAML::Token::Type&, "
    "std::string&&)";
inline constexpr std::string_view TOKENIZER_CREATESINGLETOKEN_3 =
    "Tokenizer::createSingleToken(pone::YAML::SingleToken&)";
inline constexpr std::string_view TOKENIZER_DASH = "dash()";

}  // namespace YAML::name

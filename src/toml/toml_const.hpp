/*   Created:  2025-05-24
 *   Modified: 2026-05-24
 */

#pragma once

#include <string_view>

namespace pone::TOML::name {

// +--------------------------------+
// + TOML global constants          +
// +--------------------------------+

inline constexpr std::string_view TOML_GLOBAL_NAMESPACE = "pone::TOML::";
inline constexpr std::string_view ERR_FILE = "./errlog.txt";
inline constexpr std::string_view NO_ERR_LOCATION = "<unknown>";

// +--------------------------------+
// + TOML Tokenizer constants       +
// +--------------------------------+

// Start of TOML::Token constants

inline constexpr std::string_view TOKEN_TOKEN_1 =
    "Token::Token(const std::shared_ptr<pone::TOML::Token>, const std::string "
    "&, "
    "const Token::Class &)";
inline constexpr std::string_view TOKEN_TOKEN_2 =
    "Token::Token(const std::shared_ptr<pone::TOML::Token>, const std::string "
    "&, "
    "const "
    "pone::TOML::Token::Type &";
inline constexpr std::string_view TOKEN_GETCLASS = "Token::getClass()";
inline constexpr std::string_view TOKEN_GETDEPTH = "Token::getDepth()";
inline constexpr std::string_view TOKEN_GETNAME = "Token::getName()";
inline constexpr std::string_view TOKEN_GETPARENT = "Token::getParent()";
inline constexpr std::string_view TOKEN_GETTYPE = "Token::getType()";
inline constexpr std::string_view TOKEN_PRINTENTRY =
    "Token::printEntry(std::ostream&, std::vector<std::string>&, const "
    "std::string&)";
inline constexpr std::string_view TOKEN_SETDEPTH = "Token::setDepth()";
inline constexpr std::string_view TOKEN_SETNAME = "Token::setName()";
inline constexpr std::string_view TOKEN_SETTYPE =
    "Token::setType(const pone::TOML::Token::Type&)";
inline constexpr std::string_view TOKEN_CLONE =
    "Token::clone(std::shared_ptr<pone::TOML::Token>)";
inline constexpr std::string_view TOKEN_GETPTR = "Token::getPtr()";
inline constexpr std::string_view TOKEN_PRINT =
    "Token::print(const std::ostream&, std::vector<std::string>&, const "
    "std::string&)";
inline constexpr std::string_view TOKEN_SETPARENT =
    "Token::setParent(const std::shared_ptr<pone::TOML::Token>&)";

// Start of TOML::SingleToken constants

inline constexpr std::string_view TOKEN_GETDATA = "Token::getData()";
inline constexpr std::string_view TOKEN_SETDATA =
    "Token::setData(const std::string&)";
inline constexpr std::string_view STOK_GETDATA = "SingleToken::getData()";
inline constexpr std::string_view STOK_SETDATA = "SingleToken::setData()";

// End of TOML::SingleToken constants

// Start of TOML::GroupToken constants

inline constexpr std::string_view TOKEN_CLEAR = "Token::clear()";
inline constexpr std::string_view TOKEN_COPY = "Token::copy()";
inline constexpr std::string_view TOKEN_GETTOKENS = "Token::getTokens()";
inline constexpr std::string_view TOKEN_INSERT =
    "Token::insert(std::shared_ptr<pone::TOML::Token>)";
inline constexpr std::string_view TOKEN_EMPTY = "Token::empty()";
inline constexpr std::string_view TOKEN_RELEASE = "Token::release()";
inline constexpr std::string_view TOKEN_SIZE = "Token::size()";
inline constexpr std::string_view GTOK_CLEAR = "GroupToken::clear()";
inline constexpr std::string_view GTOK_COPY = "GroupToken::copy()";
inline constexpr std::string_view GTOK_GETTOKENS = "GroupToken::getTokens()";
inline constexpr std::string_view GTOK_INSERT =
    "GroupToken::insert(std::shared_ptr<pone::TOML::Token>)";
inline constexpr std::string_view GTOK_EMPTY = "GroupToken::empty()";
inline constexpr std::string_view GTOK_RELEASE = "GroupToken::release()";
inline constexpr std::string_view GTOK_SIZE = "GroupToken::size()";

// End of TOML::GroupToken constants

// End of TOML::Token constants

// Start of TOML::Tokenizer constants

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
inline constexpr std::string_view TOKENIZER_ARRAY = "Tokenizer::array()";
inline constexpr std::string_view TOKENIZER_CLEARBUF = "Tokenizer::clearBuf()";
inline constexpr std::string_view TOKENIZER_COMMA = "Tokenizer::comma()";
inline constexpr std::string_view TOKENIZER_COMMENT = "Tokenizer::comment()";
inline constexpr std::string_view TOKENIZER_CREATEGROUPTOKEN =
    "Tokenizer::createGroupToken(const pone::TOML::Token::Type&)";
inline constexpr std::string_view TOKENIZER_CREATEGROUPTOKEN_2 =
    "Tokenizer::createGroupToken(pone::TOML::GroupToken&)";
inline constexpr std::string_view TOKENIZER_CREATESINGLETOKEN =
    "Tokenizer::createSingleToken(const pone::TOML::Token::Type&)";
inline constexpr std::string_view TOKENIZER_CREATESINGLETOKEN_2 =
    "Tokenizer::createSingleToken(const pone::TOML::Token::Type&, "
    "std::string&&)";
inline constexpr std::string_view TOKENIZER_CREATESINGLETOKEN_3 =
    "Tokenizer::createSingleToken(pone::TOML::SingleToken&)";
inline constexpr std::string_view TOKENIZER_DQ = "Tokenizer::doubleQuote()";
inline constexpr std::string_view TOKENIZER_ESC = "Tokenizer::escape()";
inline constexpr std::string_view TOKENIZER_INDENT = "Tokenizer::indent()";
inline constexpr std::string_view TOKENIZER_INSERTGROUPTOKEN =
    "Tokenizer::insertGroupToken(const pone::TOML::Token::Type&)";
inline constexpr std::string_view TOKENIZER_INSERTGROUPTOKEN_2 =
    "Tokenizer::insertGroupToken(const "
    "pone::TOML::Token::Type&)";
inline constexpr std::string_view TOKENIZER_INSERTSINGLETOKEN =
    "Tokenizer::insertSingleToken(const "
    "std::shared_ptr<pone::TOML::SingleToken &)";
inline constexpr std::string_view TOKENIZER_INSERTSINGLETOKEN_2 =
    "Tokenizer::insertSingleToken(const "
    "pone::TOML::Token::Type>&, std::string &&)";
inline constexpr std::string_view TOKENIZER_INSERTSINGLETOKEN_3 =
    "Tokenizer::insertSingleToken(const "
    "std::shared_ptr<yaml::pone::SingleToken> &";
inline constexpr std::string_view TOKENIZER_KEY =
    "Tokenizer::insertSingleToken(const std::string_view&)";
inline constexpr std::string_view TOKENIZER_LBCE = "Tokenizer::leftBrace()";
inline constexpr std::string_view TOKENIZER_LBKT = "Tokenizer::leftBracket()";
inline constexpr std::string_view TOKENIZER_LITERAL = "Tokenizer::literal()";
inline constexpr std::string_view TOKENIZER_LOOKAHEAD =
    "Tokenizer::lookahead()";
inline constexpr std::string_view TOKENIZER_MAPPING = "Tokenizer::mapping()";
inline constexpr std::string_view TOKENIZER_NL = "Tokenizer::newline()";
inline constexpr std::string_view TOKENIZER_NEXT = "Tokenizer::next()";
inline constexpr std::string_view TOKENIZER_NUMSIGN = "Tokenizer::numSign()";
inline constexpr std::string_view TOKENIZER_PRINT = "Tokenizer::print()";
inline constexpr std::string_view TOKENIZER_QUOTED = "Tokenizer::quoted()";
inline constexpr std::string_view TOKENIZER_RBCE = "Tokenizer::rightBrace()";
inline constexpr std::string_view TOKENIZER_RBKT = "Tokenizer::rightBracket()";
inline constexpr std::string_view TOKENIZER_TABLE = "Tokenizer::rightBracket()";
inline constexpr std::string_view TOKENIZER_VAL = "Tokenizer::value()";
inline constexpr std::string_view TOKENIZER_WS = "Tokenizer::whitespace()";

} // namespace pone::TOML::name

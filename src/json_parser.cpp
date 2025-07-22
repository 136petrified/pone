/*   Created:  07-17-2025
 *   Modified: 07-21-2025
 */

#include "json_parser.hpp"

#include <cctype>
#include <stdexcept>

namespace JSON {
Parser::Parser() {}

Parser::Parser(const Tokenizer &tokenizer, const std::string &file_name)
    : m_endOfTokens{false}, m_tokenIndex{1}, m_tokens{tokenizer.getTokens()} {
    m_currentToken = (m_tokens.empty()) ? "" : m_tokens[0];
}

void Parser::expr() {
    if (m_currentToken == "boards") {
        next();  // Consume "boards"
        symbol();
    } else if (m_currentToken == "board") {
        next();  // Consume "board"
        symbol();
    } else if (m_currentToken == "tiles") {
        next();
        symbol();
    } else if (m_currentToken == "gates") {
        next();
        symbol();
    }
}

bool Parser::isAlnum(std::string &s) {
    for (char &c : s) {
        if (!std::isalnum(c)) return false;
    }

    return true;
}

bool Parser::isAlpha(std::string &s) {
    for (char &c : s) {
        if (!std::isalpha(c)) return false;
    }

    return true;
}

bool Parser::isDigit(std::string &s) {
    for (char &c : s) {
        if (!std::isdigit(c)) return false;
    }

    return true;
}

bool Parser::isSymbol(std::string &s) {
    for (char &c : s) {
        if (!std::ispunct(c)) return false;
    }

    return true;
}

void Parser::next() {
    try {
        m_currentToken = m_tokens.at(m_tokenIndex++);
    } catch (std::out_of_range &) {
        m_endOfTokens = true;
    }
}

void Parser::parse() {
    while (!m_endOfTokens) {
        if (isSymbol(m_currentToken)) {
            symbol();
        } else if (isAlnum(m_currentToken)) {
            expr();
        }
    }
}

void Parser::symbol() {
    if (m_currentToken == "(") {
        next();  // Consume '(' token;
        while (m_currentToken != ")") {
            paren();
        }
    } else if (m_currentToken == "[") {
        next();
        while (m_currentToken != "]") {
            squareBracket();
        }
    } else if (m_currentToken == "{") {
        next();
        while (m_currentToken != "}") {
            curlyBracket();
        }
    } else if (m_currentToken == ":") {
        next();
    } else if (m_currentToken != ",") {
        next();
    }
}

}  // namespace JSON

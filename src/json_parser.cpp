/*   Created:  07-17-2025
 *   Modified: 07-18-2025
 */

#include "json_parser.hpp"

#include <cctype>
#include <stdexcept>

namespace JSON {
Parser::Parser() {}

Parser::Parser(const Tokenizer &tokenizer)
    : m_stop{false}, m_tc{1}, m_tokens{tokenizer.getTokens()} {
    m_currentToken = (m_tokens.empty()) ? "" : m_tokens[0];
}

void Parser::expr() {
    if (m_currentToken == "board") {
    }
}

void Parser::next() {
    try {
        m_currentToken = m_tokens.at(m_tc++);
    } catch (std::out_of_range &) {
        m_stop = true;
    }
}

void Parser::parse() {
    while (!m_stop) {
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
        if (!std::isalpha(c)) return false;
    }

    return true;
}

bool Parser::isSymbol(std::string &s) {
    for (char &c : s) {
        if (!std::ispunct(c)) return false;
    }

    return true;
}

}  // namespace JSON

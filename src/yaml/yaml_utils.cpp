/*   Created:  07-21-2025
 *   Modified: 12-28-2025
 */

#include "yaml_utils.hpp"
#include <cctype>

namespace YAML {
bool isAlnum(char &c) {
    return std::isalnum(c);
}

bool isAlnum(const char *s) {
    for (const char *p = s; *p != '\0'; ++p) {
        if (!std::isalnum(*p))
            return false;
    }

    return true;
}

bool isAlnum(std::string &s) {
    for (char &c : s) {
        if (!std::isalnum(c))
            return false;
    }

    return true;
}

bool isAlpha(char &c) {
    return isalpha(c);
}

bool isAlpha(const char *s) {
    for (const char *p = s; *p != '\0'; ++p) {
        if (!std::isalpha(*p))
            return false;
    }

    return true;
}

bool isAlpha(std::string &s) {
    for (char &c : s) {
        if (!std::isalpha(c))
            return false;
    }

    return true;
}

bool isDigit(char &c) {
    return std::isdigit(c);
}

bool isDigit(const char *s) {
    for (const char *p = s; *p != '\0'; ++p) {
        if (!std::isdigit(*p))
            return false;
    }

    return true;
}

bool isDigit(std::string &s) {
    for (char &c : s) {
        if (!std::isdigit(c))
            return false;
    }

    return true;
}

bool isQuote(char &c) {
    return c == '"' || c == '\'';
}

bool isSpace(char &c) {
    return std::isspace(c);
}

bool isSpace(const char *s) {
    for (const char *p = s; *p != '\0'; ++p) {
        if (!std::isspace(*p))
            return false;
    }

    return true;
}

bool isSpace(std::string &s) {
    for (char &c : s) {
        if (!std::isspace(c))
            return false;
    }

    return true;
}

bool isSymbol(char &c) {
    return std::ispunct(c);
}

bool isSymbol(const char *s) {
    for (const char *p = s; *p != '\0'; ++p) {
        if (!std::ispunct(*p))
            return false;
    }

    return true;
}

bool isSymbol(std::string &s) {
    for (char &c : s) {
        if (!std::ispunct(c))
            return false;
    }

    return true;
}
}  // namespace YAML

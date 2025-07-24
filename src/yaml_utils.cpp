/*   Created:  07-21-2025
 *   Modified: 07-23-2025
 */

#include "yaml_utils.hpp"

#include <cctype>

namespace YAML {
bool isAlnum(std::string &s) {
    for (char &c : s) {
        if (!std::isalnum(c)) return false;
    }

    return true;
}

bool isAlpha(std::string &s) {
    for (char &c : s) {
        if (!std::isalpha(c)) return false;
    }

    return true;
}

bool isDigit(std::string &s) {
    for (char &c : s) {
        if (!std::isdigit(c)) return false;
    }

    return true;
}

bool isSymbol(std::string &s) {
    for (char &c : s) {
        if (!std::ispunct(c)) return false;
    }

    return true;
}
}  // namespace YAML

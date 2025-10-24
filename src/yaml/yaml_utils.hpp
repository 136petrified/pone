/*   Created:  07-21-2025
 *   Modified: 10-23-2025
 */

#pragma once

#include <string>

namespace YAML {
bool isAlnum(char &c);
bool isAlnum(std::string &s);
bool isAlpha(char &c);
bool isAlpha(std::string &s);
bool isDigit(char &c);
bool isDigit(std::string &s);
bool isQuote(char &c);
bool isSpace(char &c);
bool isSpace(std::string &s);
bool isSymbol(char &c);
bool isSymbol(std::string &s);

}  // namespace YAML

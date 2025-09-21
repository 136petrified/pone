/*   Created:  07-21-2025
 *   Modified: 07-30-2025
 */

#include <string>

#ifndef PONE_YAML_UTIL_HPP
#define PONE_YAML_UTIL_HPP

namespace YAML {
bool isAlnum(char &c);
bool isAlnum(std::string &s);
bool isAlpha(char &c);
bool isAlpha(std::string &s);
bool isDigit(char &c);
bool isDigit(std::string &s);
bool isSymbol(char &c);
bool isSymbol(std::string &s);
bool isSpace(char &c);
bool isSpace(std::string &s);

}  // namespace YAML

#endif  // PONE_YAML_UTIL_HPP

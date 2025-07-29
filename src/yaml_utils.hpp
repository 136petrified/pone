/*   Created:  07-21-2025
 *   Modified: 07-28-2025
 */

#include <exception>
#include <string>

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

class EndOfIfstreamException : std::exception {
   public:
    EndOfIfstreamException()
        : msg{"EndOfIstreamException: Reached end of file"} {}
    const char *what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
};
}  // namespace YAML

/*   Created:  09-20-2025
 *   Modified: 09-20-2025
 */

#ifndef PONE_YAML_EXCEPTION_HPP
#define PONE_YAML_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace YAML {
class EndOfIfstreamException : std::runtime_error {
   public:
    EndOfIfstreamException()
        : std::runtime_error("EndOfIfstreamException: Reached enf of file."),
          m_Msg{"EndOfIfstreamException: Reached end of file."} {}
    const std::string &getMessage() const { return m_Msg; }

   private:
    std::string m_Msg;
};

class NullTokenException : std::runtime_error {
   public:
    NullTokenException()
        : std::runtime_error(
              "NullTokenException: Attempted to tokenize a null pointer."),
          m_Msg{"NullTokenException: Attempted to tokenize a null pointer."} {}
    const std::string &getMessage() const { return m_Msg; }

   private:
    std::string m_Msg;
};

}  // namespace YAML

#endif  // PONE_YAML_EXCEPTION_HPP

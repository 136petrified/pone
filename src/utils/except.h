/*   Created:  2026-01-06
 *   Modified: 2026-05-04
 */

#pragma once

#include <string>

namespace pone {

/* Default filename for error output. */
constexpr std::string ERR_FILE = "./errlog.txt";

/* Class for creating error messages. */
class ErrorMessage {
    // +--------------------------------+
    // + ErrorMessage data members      +
    // +--------------------------------+
    std::string m_msg;   // The combined error message.
    std::string m_func;  // Name of the function the exception is thrown in.
    std::string m_desc;  // The error description.
    std::string m_scope; // Name of the current scope.

  public:
    /**
     * Constructs an error message.
     *
     * @param scope the namespace of the function.
     * @param func the name of the current scope.
     * @param msg an error message.
     */
    ErrorMessage(const std::string_view &scope, const std::string_view &func,
                 const std::string &desc);

    /**
     * Gets the string representation of the
     * error message.
     */
    std::string toString() const;

    /**
     * Defines the operator << for output.
     *
     * @note Friend function of the ErrorMessage class.
     * @param out the output stream.
     * @param e an ErrorMessage reference.
     * @return a reference to the output stream
     */
    friend std::ostream &operator<<(std::ostream &out, const ErrorMessage &e);
};

} // namespace pone

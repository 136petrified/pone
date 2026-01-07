/*   Created:  01-03-2026
 *   Modified: 01-06-2026
 */

#pragma once

#include <string>

namespace pone {

/* Class for creating error messages. */
struct ErrorMessage {
    // +--------------------------------+
    // + ErrorMessage data members      +
    // +--------------------------------+
    std::string m_fmsg;   // The combined error message.
    std::string m_func;   // Name of the function the exception is thrown in.
    std::string m_msg;    // The error message.
    std::string m_scope;  // Name of the current scope.

    /* Constructs an error message.
     *
     * @param scope the namespace of the function.
     * @param func the name of the current scope.
     * @param msg an error message.
     */
    ErrorMessage(const std::string_view &scope,
                 const std::string_view &func,
                 const std::string &msg);

    /* Defines the operator << for output.
     *
     * @note Friend function of the ErrorMessage class.
     * @param out the output stream.
     * @param e an ErrorMessage reference.
     * @return a reference to the output stream
     */
    friend std::ostream &operator<<(std::ostream &out, const ErrorMessage &e);
};

}  // namespace pone

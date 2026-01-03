/*   Created:  01-03-2026
 *   Modified: 01-03-2026
 */

#include "except.h"
#include <format>

namespace pone {

ErrorMessage::ErrorMessage(const std::string_view &scope,
                           const std::string_view &func,
                           const std::string &msg)
    : m_func{func}, m_msg{msg}, m_scope{scope} {
    m_fmsg = std::format("{}{}: {}", scope, func, msg);
}

std::ostream &operator<<(std::ostream &out, const ErrorMessage &e) {
    out << e.m_fmsg;
    return out;
}

}  // namespace pone

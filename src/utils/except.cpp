/*   Created:  2026-01-02
 *   Modified: 2026-03-03
 */

#include "except.h"
#include <format>

namespace pone {

ErrorMessage::ErrorMessage(const std::string_view &scope,
                           const std::string_view &func,
                           const std::string &desc)
    : m_func{func}, m_desc{desc}, m_scope{scope} {
    m_msg = std::format("{}{}: {}", scope, func, desc);
}

std::string ErrorMessage::getString() const {
    return m_msg;
}

std::ostream &operator<<(std::ostream &out, const ErrorMessage &e) {
    out << e.m_msg;
    return out;
}

}  // namespace pone

/*   Created:  09-20-2025
 *   Modified: 10-23-2025
 */

#include "yaml_except.hpp"
#include <format>
#include "yaml_const.hpp"

namespace YAML {

void logToFile(const std::string &msg) {
    std::ofstream ofs{std::string(name::ERR_FILE), std::ios::app};
    ofs << msg << '\n';
    // ofs.close();
}

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

}  // namespace YAML

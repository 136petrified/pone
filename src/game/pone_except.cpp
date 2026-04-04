/*   Created:  2025-07-16
 *   Modified: 2026-04-03
 */

#include "pone_except.hpp"
#include <fstream>

namespace pone {

std::string PoneException::toString() const {
    return m_msg.toString();
}

void PoneException::logToFile(const std::string &file_name) const {
    std::ofstream ofs{file_name, std::ios::app};
    ofs << m_msg << '\n';
    ofs.close();
}

}  // namespace pone

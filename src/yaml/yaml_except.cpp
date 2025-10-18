/*   Created:  09-20-2025
 *   Modified: 10-08-2025
 */

#include "yaml_except.hpp"

#include <fstream>

namespace YAML {

void logToFile(const std::string &msg) {
    std::ofstream ofs{ERR_FILE, std::ios::app};
    ofs << msg << '\n';
    // ofs.close();
}

}  // namespace YAML

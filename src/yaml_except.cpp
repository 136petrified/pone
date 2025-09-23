/*   Created:  09-20-2025
 *   Modified: 09-22-2025
 */

#include "yaml_except.hpp"

#include <fstream>

namespace YAML {

void logToFile(const std::string &msg) {
    std::ofstream ofs{ERR_FILE, std::ios::app};
    ofs << msg << '\n';
    ofs.close();
}

void logToFile(const std::runtime_error &e) {
    std::ofstream ofs{ERR_FILE, std::ios::app};
    ofs << e.what() << '\n';
    ofs.close();
}

}  // namespace YAML

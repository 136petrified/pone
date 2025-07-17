/*   Created:  07-16-2025
 *   Modified: 07-16-2025
 */

#include "poneexcept.hpp"

#include <fstream>

void logToFile(const std::string &msg) {
    std::ofstream ofs{ERR_FILE};
    ofs << msg << '\n';
    ofs.close();
}

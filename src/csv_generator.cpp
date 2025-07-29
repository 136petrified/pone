/*   Created:  07-27-2025
 *   Modified: 07-28-2025
 */

#include "csv_generator.hpp"

#include <fstream>

namespace CSV {
CSV::CSV(const std::string &file_name) {}

void CSV::insertLine(const std::vector<std::string> &args) const {
    std::ofstream ofs{m_file_name};
    size_t numArgs = args.size();

    if (numArgs == 0) {
        ofs.close();
        return;
    }

    for (size_t i = 0; i < numArgs - 1; ++i) {
        ofs << args[i] << ',';
    }

    ofs << args.back() << '\n';
    ofs.close();
}

CSV::~CSV() {}
}  // namespace CSV

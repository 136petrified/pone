/*   Created:  07-27-2025
 *   Modified: 07-28-2025
 */

#ifndef PONE_CSV_GENERATOR
#define PONE_CSV_GENERATOR

#include <string>
#include <vector>

namespace CSV {
class CSV {
   public:
    CSV();
    void insertLine(const std::vector<std::string> &args) const;
    ~CSV();

   private:
    std::string m_file_name;
};
}  // namespace CSV

#endif  // PONE_CSV_GENERATOR

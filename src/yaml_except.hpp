/*   Created:  09-20-2025
 *   Modified: 09-20-2025
 */

#ifndef PONE_YAML_EXCEPTION_HPP
#define PONE_YAML_EXCEPTION_HPP

#include <fstream>
#include <stdexcept>
#include <string>

constexpr std::string ERR_FILE = "./errlog.txt";

namespace YAML {

class EndOfIfstreamException : std::runtime_error {
   public:
    EndOfIfstreamException()
        : std::runtime_error("Reached end of file."),
          m_Msg{"Reached end of file."} {}
    const std::string &getMessage() const { return m_Msg; }
    void logToFile() const {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << "EndOfIstreamException: " << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string m_Msg;
};

class NullTokenException : std::runtime_error {
   public:
    NullTokenException()
        : std::runtime_error("Attempted to tokenize a null pointer."),
          m_Msg{"Attempted to tokenize a null pointer."} {}
    NullTokenException(const std::string &msg)
        : std::runtime_error(msg), m_Msg{msg} {}

    const std::string &getMessage() const { return m_Msg; }
    void logToFile() const {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << "NullTokenException: " << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string m_Msg;
};

}  // namespace YAML

#endif  // PONE_YAML_EXCEPTION_HPP

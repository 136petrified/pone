/*   Created:  09-20-2025
 *   Modified: 09-22-2025
 */

#ifndef PONE_YAML_EXCEPTION_HPP
#define PONE_YAML_EXCEPTION_HPP

#include <fstream>
#include <stdexcept>
#include <string>

constexpr std::string ERR_FILE = "./errlog.txt";

void logToFile(const std::string &msg);
void logToFile(const std::runtime_error &e);

namespace YAML {

class TokenizerException : public std::runtime_error {
    // Abstract Base Class
   public:
    TokenizerException() = delete;
    TokenizerException(const std::string &msg)
        : std::runtime_error(msg), m_Name{"TokenizerException"} {}
    virtual const std::string &getMessage() const = 0;
    virtual void logToFile() const = 0;

   private:
    std::string m_Name;
};

class EndOfIfstreamException : public TokenizerException {
   public:
    EndOfIfstreamException()
        : TokenizerException(makeMessage()),
          m_Msg{makeMessage()},
          m_Name{"EndOfIfstreamException"} {}

    const std::string &getMessage() const override { return m_Msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Name << ": " << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const { return "Reached end of file."; }

    std::string m_Msg;
    std::string m_Name;
};

// Failed Allocation Error

class FailedAllocException : public TokenizerException {
   public:
    FailedAllocException()
        : TokenizerException(makeMessage()),
          m_Msg{makeMessage()},
          m_Name{"FailedAllocException"} {}

    const std::string &getMessage() const override { return m_Msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Name << ": " << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const {
        return "Failed to allocate a Token into memory.";
    }

    std::string m_Msg;
    std::string m_Name;
};

class NullTokenException : public TokenizerException {
   public:
    NullTokenException()
        : TokenizerException(makeMessage()),
          m_Msg{makeMessage()},
          m_Name{"NullTokenException"} {}
    NullTokenException(const std::string &msg)
        : TokenizerException(msg), m_Msg{msg}, m_Name{"NullTokenException"} {}

    const std::string &getMessage() const override { return m_Msg; }
    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Name << ": " << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const {
        return "Attempted to tokenize a null pointer.";
    }

    std::string m_Msg;
    std::string m_Name;
};

}  // namespace YAML

#endif  // PONE_YAML_EXCEPTION_HPP

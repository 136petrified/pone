/*   Created:  09-20-2025
 *   Modified: 09-22-2025
 */

#ifndef PONE_YAML_EXCEPTION_HPP
#define PONE_YAML_EXCEPTION_HPP

#include <fstream>
#include <stdexcept>
#include <string>

constexpr std::string ERR_FILE = "./errlog.txt";

namespace YAML {

void logToFile(const std::string &msg);

class TokenizerException : public std::runtime_error {
    // Abstract Base Class
   public:
    TokenizerException() = delete;
    TokenizerException(const std::string &name, const std::string &msg)
        : std::runtime_error(msg), m_Name{"TokenizerException"} {}
    virtual const std::string &getMessage() const = 0;
    virtual void logToFile() const = 0;

   protected:
    std::string m_Name;
};

class EmptyGroupStackException : public TokenizerException {
   public:
    EmptyGroupStackException()
        : TokenizerException("EmptyGroupStackException", makeMessage()),
          m_Msg{makeMessage()} {}

    EmptyGroupStackException(const std::string &msg)
        : TokenizerException("EmptyGroupStackException", msg), m_Msg{msg} {}

    const std::string &getMessage() const override { return m_Msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Name << ": " << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const {
        return "Attempted to get the front of the empty GroupToken stack.";
    }

    std::string m_Msg;
};

class EndOfIfstreamException : public TokenizerException {
   public:
    EndOfIfstreamException()
        : TokenizerException("EndOfIfstreamException", makeMessage()),
          m_Msg{makeMessage()} {}

    const std::string &getMessage() const override { return m_Msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Name << ": " << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const { return "Reached end of file."; }

    std::string m_Msg;
};

class FailedAllocException : public TokenizerException {
   public:
    FailedAllocException()
        : TokenizerException("FailedAllocException", makeMessage()),
          m_Msg{makeMessage()} {}

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
};

class NullTokenException : public TokenizerException {
   public:
    NullTokenException()
        : TokenizerException("NullTokenException", makeMessage()),
          m_Msg{makeMessage()} {}
    NullTokenException(const std::string &msg)
        : TokenizerException("NullTokenException", msg), m_Msg{msg} {}

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
};

class RootNotFoundException : public TokenizerException {
   public:
    RootNotFoundException()
        : TokenizerException("RootNotFoundException", makeMessage()) {}

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
};

}  // namespace YAML

#endif  // PONE_YAML_EXCEPTION_HPP

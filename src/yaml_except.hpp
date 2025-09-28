/*   Created:  09-20-2025
 *   Modified: 09-27-2025
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
        : std::runtime_error(msg), m_name{"TokenizerException"} {}
    virtual const std::string &getMessage() const = 0;
    virtual void logToFile() const = 0;

   protected:
    std::string m_name;
};

class EmptyGroupStackException : public TokenizerException {
   public:
    EmptyGroupStackException()
        : TokenizerException("EmptyGroupStackException", makeMessage()),
          m_msg{makeMessage()} {}

    EmptyGroupStackException(const std::string &msg)
        : TokenizerException("EmptyGroupStackException", msg), m_msg{msg} {}

    const std::string &getMessage() const override { return m_msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const {
        return "Attempted to get the front of the empty GroupToken stack.";
    }

    std::string m_msg;
};

class EndOfIfstreamException : public TokenizerException {
   public:
    EndOfIfstreamException()
        : TokenizerException("EndOfIfstreamException", makeMessage()),
          m_msg{makeMessage()} {}

    const std::string &getMessage() const override { return m_msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const { return "Reached end of file."; }

    std::string m_msg;
};

class FailedAllocException : public TokenizerException {
   public:
    FailedAllocException()
        : TokenizerException("FailedAllocException", makeMessage()),
          m_msg{makeMessage()} {}

    const std::string &getMessage() const override { return m_msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const {
        return "Failed to allocate a Token into memory.";
    }

    std::string m_msg;
};

class NotAGroupException : public TokenizerException {
   public:
    NotAGroupException()
        : TokenizerException("NotAGroupException", makeMessage()),
          m_msg{makeMessage()} {}

    const std::string &getMessage() const override { return m_msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const {
        return "The Token passed is not of type Group.";
    }

    std::string m_msg;
};

class NotASingleException : public TokenizerException {
   public:
    NotASingleException()
        : TokenizerException("NotASingleException", makeMessage()),
          m_msg{makeMessage()} {}

    const std::string &getMessage() const override { return m_msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const {
        return "The Token passed is not of type Single.";
    }

    std::string m_msg;
};

class NullTokenException : public TokenizerException {
   public:
    NullTokenException()
        : TokenizerException("NullTokenException", makeMessage()),
          m_msg{makeMessage()} {}
    NullTokenException(const std::string &msg)
        : TokenizerException("NullTokenException", msg), m_msg{msg} {}

    const std::string &getMessage() const override { return m_msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const {
        return "Attempted to tokenize a null pointer.";
    }

    std::string m_msg;
};

class RootNotFoundException : public TokenizerException {
   public:
    RootNotFoundException()
        : TokenizerException("RootNotFoundException", makeMessage()) {}

    const std::string &getMessage() const override { return m_msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const {
        return "Attempted to tokenize a null pointer.";
    }

    std::string m_msg;
};

}  // namespace YAML

#endif  // PONE_YAML_EXCEPTION_HPP

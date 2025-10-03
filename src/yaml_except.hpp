/*   Created:  09-20-2025
 *   Modified: 10-03-2025
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
        : std::runtime_error(msg), m_msg{msg}, m_name{"TokenizerException"} {}
    const std::string &getMessage() { return m_msg; }
    void logToFile() const {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   protected:
    std::string m_msg;
    std::string m_name;
};

class EmptyGroupStackException : public TokenizerException {
   public:
    EmptyGroupStackException()
        : TokenizerException("EmptyGroupStackException", makeMessage()) {}
    EmptyGroupStackException(const std::string &msg)
        : TokenizerException("EmptyGroupStackException", msg) {}

   private:
    std::string makeMessage() const {
        return "Attempted to get the front of the empty GroupToken stack.";
    }
};

class EndOfIfstreamException : public TokenizerException {
   public:
    EndOfIfstreamException()
        : TokenizerException("EndOfIfstreamException", makeMessage()) {}
    EndOfIfstreamException(const std::string &msg)
        : TokenizerException("EndOfIfstreamException", msg) {}

   private:
    std::string makeMessage() const { return "Reached end of file."; }
};

class FailedAllocException : public TokenizerException {
   public:
    FailedAllocException()
        : TokenizerException("FailedAllocException", makeMessage()) {}
    FailedAllocException(const std::string &msg)
        : TokenizerException("FailedAllocException", msg) {}

   private:
    std::string makeMessage() const {
        return "Failed to allocate a Token into memory.";
    }
};

class InvalidMappingException : public TokenizerException {
   public:
    InvalidMappingException()
        : TokenizerException("InvalidMappingException", makeMessage()) {}
    InvalidMappingException(const std::string &msg)
        : TokenizerException("InvalidMappingException", msg) {}

   private:
    std::string makeMessage() const {
        return "A mapping was malformed (not made correctly).";
    }
};

class InvalidSequenceException : public TokenizerException {
   public:
    InvalidSequenceException()
        : TokenizerException("InvalidSequenceException", makeMessage()) {}
    InvalidSequenceException(const std::string &msg)
        : TokenizerException("InvalidSequenceException", msg) {}

   private:
    std::string makeMessage() const {
        return "A sequence was malformed (not made correctly).";
    }
};

class NotAGroupException : public TokenizerException {
   public:
    NotAGroupException()
        : TokenizerException("NotAGroupException", makeMessage()) {}
    NotAGroupException(const std::string &msg)
        : TokenizerException("NotAGroupException", msg) {}

   private:
    std::string makeMessage() const {
        return "The Token passed is not of type Group.";
    }
};

class NotASingleException : public TokenizerException {
   public:
    NotASingleException()
        : TokenizerException("NotASingleException", makeMessage()) {}
    NotASingleException(const std::string &msg)
        : TokenizerException("NotASingleException", msg) {}

   private:
    std::string makeMessage() const {
        return "The Token passed is not of type Single.";
    }
};

class NullTokenException : public TokenizerException {
   public:
    NullTokenException()
        : TokenizerException("NullTokenException", makeMessage()) {}
    NullTokenException(const std::string &msg)
        : TokenizerException("NullTokenException", msg) {}

   private:
    std::string makeMessage() const {
        return "Attempted to tokenize a null pointer.";
    }
};

class RootNotFoundException : public TokenizerException {
   public:
    RootNotFoundException()
        : TokenizerException("RootNotFoundException", makeMessage()) {}
    RootNotFoundException(const std::string &msg)
        : TokenizerException("RootNotFoundException", msg) {}

   private:
    std::string makeMessage() const { return "Failed to find root Token!"; }
};

class SelfParentInsertionException : public TokenizerException {
   public:
    SelfParentInsertionException()
        : TokenizerException("SelfParentInsertionException", makeMessage()) {}
    SelfParentInsertionException(const std::string &msg)
        : TokenizerException("SelfParentInsertionException", msg) {}

   private:
    std::string makeMessage() const {
        return "Attempted to insert a parent GroupToken into itself.";
    }
};

}  // namespace YAML

#endif  // PONE_YAML_EXCEPTION_HPP

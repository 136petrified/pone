/*   Created:  09-20-2025
 *   Modified: 10-16-2025
 */

#ifndef PONE_YAML_EXCEPTION_HPP
#define PONE_YAML_EXCEPTION_HPP

#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>

namespace YAML {

constexpr std::string ERR_FILE        = "./errlog.txt";
constexpr std::string NO_ERR_LOCATION = "<unknown>";

// NOTE: string views should be converted to std::string
//       whenever possible

void logToFile(const std::string &msg);

class TokenizerException : public std::runtime_error {
    // Abstract Base Class
   protected:
    std::string m_location;
    std::string m_msg;
    std::string m_name;

   public:
    TokenizerException() = delete;
    TokenizerException(const std::string &location,
                       const std::string &name,
                       const std::string &msg)
        : std::runtime_error(msg), m_msg{msg}, m_name{"TokenizerException"} {}
    const std::string_view getLocation() const {
        return std::string_view(m_location);
    }
    const std::string_view getMessage() const {
        return std::string_view(m_msg);
    }
    void logToFile() const {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << "In \"" << m_location << "\" -> " << m_name << ": " << m_msg
            << '\n';
        // ofs.close();
    }
};

class EmptyGroupStackException : public TokenizerException {
   public:
    EmptyGroupStackException()
        : TokenizerException(NO_ERR_LOCATION,
                             "EmptyGroupStackException",
                             makeMessage()) {}
    EmptyGroupStackException(const std::string &location,
                             const std::string &func)
        : TokenizerException(location,
                             "EmptyGroupStackException",
                             makeMessage()) {}
    EmptyGroupStackException(const std::string &location,
                             const std::string &func,
                             const std::string &msg)
        : TokenizerException(location, "EmptyGroupStackException", msg) {}

   private:
    std::string makeMessage() const {
        return "Attempted to get the front of the empty GroupToken stack.";
    }
};

class EndOfIfstreamException : public TokenizerException {
   public:
    EndOfIfstreamException()
        : TokenizerException(NO_ERR_LOCATION,
                             "EndOfIfstreamException",
                             makeMessage()) {}
    EndOfIfstreamException(const std::string &location, const std::string &func)
        : TokenizerException(location,
                             "EndOfIfstreamException",
                             makeMessage()) {}
    EndOfIfstreamException(const std::string &location,
                           const std::string &func,
                           const std::string &msg)
        : TokenizerException(location, "EndOfIfstreamException", msg) {}

   private:
    std::string makeMessage() const { return "Reached end of file."; }
};

class FailedAllocException : public TokenizerException {
   public:
    FailedAllocException()
        : TokenizerException(NO_ERR_LOCATION,
                             "FailedAllocException",
                             makeMessage()) {}
    FailedAllocException(const std::string &location, const std::string &func)
        : TokenizerException(location, "FailedAllocException", makeMessage()) {}
    FailedAllocException(const std::string &location,
                         const std::string &func,
                         const std::string &msg)
        : TokenizerException(location, "FailedAllocException", msg) {}

   private:
    std::string makeMessage() const {
        return "Failed to allocate a Token into memory.";
    }
};

class InvalidKeyException : public TokenizerException {
   public:
    InvalidKeyException()
        : TokenizerException(NO_ERR_LOCATION,
                             "InvalidKeyException",
                             makeMessage()) {}
    InvalidKeyException(const std::string &location, const std::string &func)
        : TokenizerException(location, "InvalidKeyException", makeMessage()) {}
    InvalidKeyException(const std::string &location,
                        const std::string &func,
                        const std::string &msg)
        : TokenizerException(location, "InvalidKeyException", msg) {}

   private:
    std::string makeMessage() const {
        return "A key was malformed (not made correctly).";
    }
};

class InvalidMappingException : public TokenizerException {
   public:
    InvalidMappingException()
        : TokenizerException(NO_ERR_LOCATION,
                             "InvalidMappingException",
                             makeMessage()) {}
    InvalidMappingException(const std::string &location,
                            const std::string &func)
        : TokenizerException(location,
                             "InvalidMappingException",
                             makeMessage()) {}
    InvalidMappingException(const std::string &location,
                            const std::string &func,
                            const std::string &msg)
        : TokenizerException(location, "InvalidMappingException", msg) {}

   private:
    std::string makeMessage() const {
        return "A mapping was malformed (not made correctly).";
    }
};

class InvalidSequenceException : public TokenizerException {
   public:
    InvalidSequenceException()
        : TokenizerException(NO_ERR_LOCATION,
                             "InvalidSequenceException",
                             makeMessage()) {}
    InvalidSequenceException(const std::string &location,
                             const std::string &func)
        : TokenizerException(location,
                             "InvalidSequenceException",
                             makeMessage()) {}
    InvalidSequenceException(const std::string &location,
                             const std::string &func,
                             const std::string &msg)
        : TokenizerException(location, "InvalidSequenceException", msg) {}

   private:
    std::string makeMessage() const {
        return "A sequence was malformed (not made correctly).";
    }
};

class InvalidValueException : public TokenizerException {
   public:
    InvalidValueException()
        : TokenizerException(NO_ERR_LOCATION,
                             "InvalidValueException",
                             makeMessage()) {}
    InvalidValueException(const std::string &location, const std::string &func)
        : TokenizerException(location, "InvalidValueException", makeMessage()) {
    }
    InvalidValueException(const std::string &location,
                          const std::string &func,
                          const std::string &msg)
        : TokenizerException(location, "InvalidValueException", msg) {}

   private:
    std::string makeMessage() const {
        return "A value was malformed (not made correctly).";
    }
};

class NotAGroupException : public TokenizerException {
   public:
    NotAGroupException()
        : TokenizerException(NO_ERR_LOCATION,
                             "NotAGroupException",
                             makeMessage()) {}
    NotAGroupException(const std::string &location, const std::string &func)
        : TokenizerException(location, "NotAGroupException", makeMessage()) {}
    NotAGroupException(const std::string &location,
                       const std::string &func,
                       const std::string &msg)
        : TokenizerException(location, "NotAGroupException", msg) {}

   private:
    std::string makeMessage() const {
        return "The Token passed is not of type Group.";
    }
};

class NotASingleException : public TokenizerException {
   public:
    NotASingleException()
        : TokenizerException(NO_ERR_LOCATION,
                             "NotASingleException",
                             makeMessage()) {}
    NotASingleException(const std::string &location, const std::string &func)
        : TokenizerException(location, "NotASingleException", makeMessage()) {}
    NotASingleException(const std::string &location,
                        const std::string &func,
                        const std::string &msg)
        : TokenizerException(location, "NotASingleException", msg) {}

   private:
    std::string makeMessage() const {
        return "The Token passed is not of type Single.";
    }
};

class NullTokenException : public TokenizerException {
   public:
    NullTokenException()
        : TokenizerException(NO_ERR_LOCATION,
                             "NullTokenException",
                             makeMessage()) {}
    NullTokenException(const std::string &location, const std::string &func)
        : TokenizerException(location, "NullTokenException", makeMessage()) {}
    NullTokenException(const std::string &location,
                       const std::string &func,
                       const std::string &msg)
        : TokenizerException(location, "NullTokenException", msg) {}

   private:
    std::string makeMessage() const {
        return "Attempted to tokenize a null pointer.";
    }
};

class RootNotFoundException : public TokenizerException {
   public:
    RootNotFoundException()
        : TokenizerException(NO_ERR_LOCATION,
                             "RootNotFoundException",
                             makeMessage()) {}
    RootNotFoundException(const std::string &location, const std::string &func)
        : TokenizerException(location, "RootNotFoundException", makeMessage()) {
    }
    RootNotFoundException(const std::string &location,
                          const std::string &func,
                          const std::string &msg)
        : TokenizerException(location, "RootNotFoundException", msg) {}

   private:
    std::string makeMessage() const { return "Failed to find root Token!"; }
};

class SelfParentInsertionException : public TokenizerException {
   public:
    SelfParentInsertionException()
        : TokenizerException(NO_ERR_LOCATION,
                             "SelfParentInsertionException",
                             makeMessage()) {}
    SelfParentInsertionException(const std::string &location,
                                 const std::string &func)
        : TokenizerException(location,
                             "SelfParentInsertionException",
                             makeMessage()) {}
    SelfParentInsertionException(const std::string &location,
                                 const std::string &func,
                                 const std::string &msg)
        : TokenizerException(location, "SelfParentInsertionException", msg) {}

   private:
    std::string makeMessage() const {
        return "Attempted to insert a parent GroupToken into itself.";
    }
};

}  // namespace YAML

#endif  // PONE_YAML_EXCEPTION_HPP

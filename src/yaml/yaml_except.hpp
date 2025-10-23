/*   Created:  09-20-2025
 *   Modified: 10-23-2025
 */

#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include "yaml_const.hpp"

namespace YAML {

struct ErrorMessage {
    std::string m_fmsg;
    std::string m_func;
    std::string m_msg;
    std::string m_scope;

    ErrorMessage(const std::string_view &scope,
                 const std::string_view &func,
                 const std::string &msg);

    friend std::ostream &operator<<(std::ostream &out, const ErrorMessage &e);
};

// NOTE: string views should be converted to std::string
//       whenever possible

void logToFile(const std::string &msg);

class TokenizerException : public std::runtime_error {
    // Abstract Base Class
   protected:
    ErrorMessage m_err;
    std::string m_location;
    std::string m_name;

   public:
    TokenizerException() = delete;
    TokenizerException(const ErrorMessage &e)
        : std::runtime_error(e.m_msg),
          m_err{e},
          m_location{e.m_scope + e.m_func},
          m_name{"TokenizerException"} {}
    const std::string_view getLocation() const {
        return std::string_view(m_location);
    }
    const std::string_view getMessage() const {
        return std::string_view(m_err.m_msg);
    }
    void logToFile() const {
        std::ofstream ofs{std::string(name::ERR_FILE), std::ios::app};
        ofs << m_name << "at:" << m_err << '\n';
    }
};

class EmptyGroupStackException : public TokenizerException {
   public:
    EmptyGroupStackException() = delete;
    EmptyGroupStackException(const ErrorMessage &e);
};

class EndOfIfstreamException : public TokenizerException {
   public:
    EndOfIfstreamException() = delete;
    EndOfIfstreamException(const ErrorMessage &e);
};

class FailedAllocException : public TokenizerException {
   public:
    FailedAllocException() = delete;
    FailedAllocException(const ErrorMessage &e);
};

class InvalidKeyException : public TokenizerException {
   public:
    InvalidKeyException() = delete;
    InvalidKeyException(const ErrorMessage &e);
};

class InvalidMappingException : public TokenizerException {
   public:
    InvalidMappingException() = delete;
    InvalidMappingException(const ErrorMessage &e);
};

class InvalidSequenceException : public TokenizerException {
   public:
    InvalidSequenceException() = delete;
    InvalidSequenceException(const ErrorMessage &e);
};

class InvalidValueException : public TokenizerException {
   public:
    InvalidValueException() = delete;
    InvalidValueException(const ErrorMessage &e);
};

class NotAGroupException : public TokenizerException {
   public:
    NotAGroupException() = delete;
    NotAGroupException(const ErrorMessage &e);
};

class NotASingleException : public TokenizerException {
   public:
    NotASingleException() = delete;
    NotASingleException(const ErrorMessage &e);
};

class NullTokenException : public TokenizerException {
   public:
    NullTokenException() = delete;
    NullTokenException(const ErrorMessage &e);
};

class RootNotFoundException : public TokenizerException {
   public:
    RootNotFoundException() = delete;
    RootNotFoundException(const ErrorMessage &e);
};

class SelfParentInsertionException : public TokenizerException {
   public:
    SelfParentInsertionException() = delete;
    SelfParentInsertionException(const ErrorMessage &e);
};

}  // namespace YAML

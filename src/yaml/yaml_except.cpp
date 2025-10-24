/*   Created:  09-20-2025
 *   Modified: 10-23-2025
 */

#include "yaml_except.hpp"
#include <format>
#include <fstream>
#include <string_view>
#include "yaml_const.hpp"

namespace YAML {

ErrorMessage::ErrorMessage(const std::string_view &scope,
                           const std::string_view &func,
                           const std::string &msg)
    : m_func{func}, m_msg{msg}, m_scope{scope} {
    m_fmsg = std::format("{}{}: {}", scope, func, msg);
}

std::ostream &operator<<(std::ostream &out, const ErrorMessage &e) {
    out << e.m_fmsg;
    return out;
}

void logToFile(const std::string &msg) {
    std::ofstream ofs{std::string(name::ERR_FILE), std::ios::app};
    ofs << msg << '\n';
}

TokenizerException::TokenizerException(const ErrorMessage &e,
                                       const std::string &name)
    : std::runtime_error(e.m_msg),
      m_err{e},
      m_location{e.m_scope + e.m_func},
      m_name{name},
      m_parent{"TokenizerException"} {}

const std::string_view TokenizerException::getLocation() const {
    return std::string_view(m_location);
}

const std::string_view TokenizerException::getMessage() const {
    return std::string_view(m_err.m_msg);
}

void TokenizerException::logToFile() const {
    std::ofstream ofs{std::string(name::ERR_FILE)};
    ofs << m_name << "at: " << m_err << '\n';
}

EmptyGroupStackException::EmptyGroupStackException(const ErrorMessage &e)
    : TokenizerException(e, "EmptyGroupStackException") {}

EndOfIfstreamException::EndOfIfstreamException(const ErrorMessage &e)
    : TokenizerException(e, "EndOfIfstreamException") {}

FailedAllocException::FailedAllocException(const ErrorMessage &e)
    : TokenizerException(e, "FailedAllocException") {}

InvalidKeyException::InvalidKeyException(const ErrorMessage &e)
    : TokenizerException(e, "FailedAllocException") {}

InvalidMappingException::InvalidMappingException(const ErrorMessage &e)
    : TokenizerException(e, "InvalidMappingException") {}

InvalidSequenceException::InvalidSequenceException(const ErrorMessage &e)
    : TokenizerException(e, "InvalidSequenceException") {}

InvalidValueException::InvalidValueException(const ErrorMessage &e)
    : TokenizerException(e, "InvalidValueException") {}

NotAGroupException::NotAGroupException(const ErrorMessage &e)
    : TokenizerException(e, "NotAGroupException") {}

NotASingleException::NotASingleException(const ErrorMessage &e)
    : TokenizerException(e, "NotASingleException") {}

NullTokenException::NullTokenException(const ErrorMessage &e)
    : TokenizerException(e, "NullTokenException") {}

RootNotFoundException::RootNotFoundException(const ErrorMessage &e)
    : TokenizerException(e, "RootNotFoundException") {}

SelfParentInsertionException::SelfParentInsertionException(
    const ErrorMessage &e)
    : TokenizerException(e, "SelfParentInsertionException") {}

}  // namespace YAML

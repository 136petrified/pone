/*   Created:  09-20-2025
 *   Modified: 01-07-2026
 */

#pragma once

#include <stdexcept>
#include <string>
#include <string_view>
#include "utils/except.h"

namespace pone::YAML {
// NOTE: string views should be converted to std::string
//       whenever possible

// +--------------------------------+
// + Utility functions              +
// +--------------------------------+

/* Logs an error message to the error log file.
 *
 * @param msg an error message.
 */
void logToFile(const std::string &msg);

// +------------------------------------+
// + Base exception classes             +
// +------------------------------------+

/* Abstract Base Exception class for the Tokenizer class. */
class TokenizerException : public std::runtime_error {
    // Abstract Base Class

    // +------------------------------------+
    // + TokenizerException data members    +
    // +------------------------------------+

   protected:
    ErrorMessage m_err;      // An ErrorMessage.
    std::string m_location;  // Name of the function the exception is thrown in.
    std::string m_name;      // Name of the function.
    std::string m_parent;    // Name of the parent exception assigned by derived
                             // classes.
   public:
    // +------------------------------------+
    // + TokenizerException constructors    +
    // +------------------------------------+

    /* Default TokenizerException constructor.
     *
     * @note Deleted function. Do not use.
     * @sa TokenizerException(const ErrorMessage &, const std::string &)
     */
    TokenizerException() = delete;

    /* TokenizerException constructor.
     *
     * @param e an ErrorMessage reference.
     * @param name the name of the function.
     */
    TokenizerException(const ErrorMessage &e, const std::string &name);

    // +------------------------------------+
    // + TokenizerException constructors    +
    // +------------------------------------+

    /* Gets the name of the function where the exception was thrown.
     *
     * @return the name of the function.
     */
    const std::string_view getLocation() const;

    /* Gets the error message.
     *
     * @return the error message.
     */
    const std::string_view getMessage() const;

    /* Logs the exception into the error log file. */
    void logToFile() const;
};

/* Exception thrown for an empty GroupToken stack.
 *
 * @sa TokenizerException
 */
class EmptyGroupStackException : public TokenizerException {
   public:
    /* Default EmptyGroupStackException constructor.
     *
     * @note Deleted function. Do not use.
     * @sa EmptyGroupStackException(const ErrorMessage &, const std::string &)
     */
    EmptyGroupStackException() = delete;

    /* EmptyGroupStackException constructor.
     *
     * @param e an ErrorMessage reference.
     */
    EmptyGroupStackException(const ErrorMessage &e);
};

/* Exception thrown when the end of a file input stream occurs.
 *
 * @sa TokenizerException
 */
class EndOfIfstreamException : public TokenizerException {
   public:
    /* Default EmptyGroupStackException constructor.
     *
     * @note Deleted function. Do not use.
     * @sa EndOfIfstreamException(const ErrorMessage &, const std::string &)
     */
    EndOfIfstreamException() = delete;

    /* EndOfIfstreamException constructor.
     *
     * @param e an ErrorMessage reference.
     */
    EndOfIfstreamException(const ErrorMessage &e);
};

/* Exception thrown for a failed memory allocation.
 *
 * @sa TokenizerException
 */
class FailedAllocException : public TokenizerException {
   public:
    /* Default FailedAllocException constructor.
     *
     * @note Deleted function. Do not use.
     * @sa FailedAllocException(const ErrorMessage &, const std::string &)
     */
    FailedAllocException() = delete;

    /* FailedAllocException constructor.
     *
     * @param e an ErrorMessage reference.
     */
    FailedAllocException(const ErrorMessage &e);
};

/* Exception thrown for an invalid Token::Key.
 *
 * @sa TokenizerException, pone::YAML::Token::Key
 */
class InvalidKeyException : public TokenizerException {
   public:
    /* Default InvalidKeyException constructor.
     *
     * @note Deleted function. Do not use.
     * @sa FailedAllocException(const ErrorMessage &, const std::string &)
     */
    InvalidKeyException() = delete;

    /* InvalidKeyException constructor.
     *
     * @param e an ErrorMessage reference.
     */
    InvalidKeyException(const ErrorMessage &e);
};

/* Exception thrown for an invalid YAML mapping.
 *
 * @note A mapping is defined as a key-value pair.
 * @sa TokenizerException
 */
class InvalidMappingException : public TokenizerException {
   public:
    /* Default InvalidMappingException constructor.
     *
     * @note Deleted function. Do not use.
     * @sa InvalidMappingException(const ErrorMessage &, const std::string &)
     */
    InvalidMappingException() = delete;

    /* InvalidMappingException constructor.
     *
     * @param e an ErrorMessage reference.
     */
    InvalidMappingException(const ErrorMessage &e);
};

/* Exception thrown for an invalid YAML sequence.
 *
 * @note A sequence is defined as a list with elements
 *       separated by hyphens.
 * @sa TokenizerException
 */
class InvalidSequenceException : public TokenizerException {
   public:
    /* Default InvalidSequenceException constructor.
     *
     * @note Deleted function. Do not use.
     * @sa InvalidSequenceException(const ErrorMessage &, const std::string &)
     */
    InvalidSequenceException() = delete;

    /* InvalidSequenceException constructor.
     *
     * @param e an ErrorMessage reference.
     */
    InvalidSequenceException(const ErrorMessage &e);
};

/* Exception thrown for an invalid YAML value.
 *
 * @sa TokenizerException
 */
class InvalidValueException : public TokenizerException {
   public:
    /* Default InvalidValueException constructor.
     *
     * @note Deleted function. Do not use.
     * @sa InvalidValueException(const ErrorMessage &, const std::string &)
     */
    InvalidValueException() = delete;

    /* InvalidValueException constructor.
     *
     * @param e an ErrorMessage reference.
     */
    InvalidValueException(const ErrorMessage &e);
};

/* Exception thrown when a non-Group token is passed as a value.
 *
 * @sa TokenizerException, pone::YAML::Token::Class::Group
 */
class NotAGroupException : public TokenizerException {
   public:
    /* Default NotAGroupException constructor.
     *
     * @note Deleted function. Do not use.
     * @sa NotAGroupException(const ErrorMessage &, const std::string &)
     */
    NotAGroupException() = delete;

    /* NotAGroupException constructor.
     *
     * @param e an ErrorMessage reference.
     */
    NotAGroupException(const ErrorMessage &e);
};

/* Exception thrown when a non-Single token is passed as a value.
 *
 * @sa TokenizerException, pone::YAML::Token::Class::Single
 */
class NotASingleException : public TokenizerException {
   public:
    /* Default NotASingleException constructor.
     *
     * @note Deleted function. Do not use.
     * @sa NotASingleException(const ErrorMessage &, const std::string &)
     */
    NotASingleException() = delete;

    /* NotASingleException constructor.
     *
     * @param e an ErrorMessage reference.
     */
    NotASingleException(const ErrorMessage &e);
};

/* Exception thrown if a token is null.
 *
 * @sa TokenizerException
 */
class NullTokenException : public TokenizerException {
   public:
    /* Default NullTokenException constructor.
     *
     * @note Deleted function. Do not use.
     * @sa NullTokenException(const ErrorMessage &, const std::string &)
     */
    NullTokenException() = delete;

    /* NullTokenException constructor.
     *
     * @param e an ErrorMessage reference.
     */
    NullTokenException(const ErrorMessage &e);
};

/* Exception thrown if a token with type Token::Root cannot be found.
 *
 * @sa TokenizerException, pone::YAML::Token::Type::Root
 */
class RootNotFoundException : public TokenizerException {
   public:
    /* Default RootNotFoundException constructor.
     *
     * @note Deleted function. Do not use.
     * @sa RootNotFoundException(const ErrorMessage &, const std::string &)
     */
    RootNotFoundException() = delete;

    /* RootNotFoundException constructor.
     *
     * @param e an ErrorMessage reference.
     */
    RootNotFoundException(const ErrorMessage &e);
};

/* Exception thrown if a Group token's parent is assigned
 * to itself.
 *
 * @sa TokenizerException
 */
class SelfParentInsertionException : public TokenizerException {
   public:
    /* Default SelfParentInsertionException constructor.
     *
     * @note Deleted function. Do not use.
     * @sa SelfParentInsertionException(const ErrorMessage &, const std::string
     * &)
     */
    SelfParentInsertionException() = delete;

    /* SelfParentInsertionException constructor.
     *
     * @param e an ErrorMessage reference.
     */
    SelfParentInsertionException(const ErrorMessage &e);
};

}  // namespace pone::YAML

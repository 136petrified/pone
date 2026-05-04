/*   Created:  2024-09-08
 *   Modified: 2026-05-04
 */

#pragma once

#include "pone_gate.hpp"
#include "pone_tile.hpp"
#include "utils/except.h"
#include <memory>

namespace pone {

using GatePtr = std::shared_ptr<Gate>;
using TilePtr = std::shared_ptr<Tile>;

/**
 * Abstract exception class for the game engine.
 */
class PoneException : public std::runtime_error {
  protected:
    std::string m_name;
    ErrorMessage m_msg;

  public:
    /**
     * Default PoneException constructor.
     *
     * @warning This constructor is deleted.
     */
    PoneException() = delete;

    /**
     * Constructs a PoneException with the exception name and message.
     *
     * @param name of the exception.
     * @param msg the error message.
     */
    PoneException(const std::string &name, const ErrorMessage &msg)
        : std::runtime_error(msg.toString()), m_name{name}, m_msg{msg} {}

    /**
     * Function for getting a formatted
     * error message.
     *
     * @returns the error message.
     */
    std::string toString() const;

    /**
     * Function for logging the error message into the
     * specified file.
     *
     * @param file_name filename to log the error to.
     */
    void logToFile(const std::string &file_name) const;
};

/**
 * Exception class for duplicate tiles.
 */
class DuplicateTilesException : public PoneException {
  public:
    /**
     * Default DuplicateTilesException constructor.
     *
     * @warning This constructor is deleted.
     */
    DuplicateTilesException() = delete;

    /**
     * Constructs a DuplicateTileException with an ErrorMessage
     * instance.
     *
     * @param msg an ErrorMessage instance.
     */
    DuplicateTilesException(const ErrorMessage &msg)
        : PoneException("DuplicateTilesException", msg) {}
};

/**
 * Exception class for invalid tiles.
 */
class InvalidTileException : public PoneException {
  public:
    /**
     * Default InvalidTileException constructor.
     *
     * @warning This constructor is deleted.
     */
    InvalidTileException() = delete;

    /**
     * Constructs an InvalidTileException with an ErrorMessage
     * instance.
     *
     * @param msg an ErrorMessage instance.
     */
    InvalidTileException(const ErrorMessage &msg)
        : PoneException("InvalidTileException", msg) {}
};

/**
 * Exception class for duplicate gates.
 */
class DuplicateGatesException : public PoneException {
  public:
    /**
     * Default DuplicateGatesException constructor.
     *
     * @warning This constructor is deleted.
     */
    DuplicateGatesException() = delete;

    /**
     * Constructs an DuplicateGatesException with an ErrorMessage
     * instance.
     *
     * @param msg an ErrorMessage instance.
     */
    DuplicateGatesException(const ErrorMessage &msg)
        : PoneException("DuplicateGatesException", msg) {}
};

/**
 * Exception class for invalid gates.
 */
class InvalidGateException : public PoneException {
  public:
    /**
     * Default InvalidGateException constructor.
     *
     * @warning This constructor is deleted.
     */
    InvalidGateException() = delete;

    /**
     * Constructs an InvalidGateException with an ErrorMessage
     * instance.
     *
     * @param msg an ErrorMessage instance.
     */
    InvalidGateException(const ErrorMessage &msg)
        : PoneException("InvalidGateException", msg) {}
};

/**
 * Exception class for invalid boards.
 */
class InvalidBoardException : public PoneException {
  public:
    /**
     * Default InvalidBoardException constructor.
     *
     * @warning This constructor is deleted.
     */
    InvalidBoardException() = delete;

    /**
     * Constructs an InvalidBoardException with an ErrorMessage
     * instance.
     *
     * @param msg an ErrorMessage instance.
     */
    InvalidBoardException(const ErrorMessage &msg)
        : PoneException("InvalidBoardException", msg) {}
};

/**
 * Exception class for invalid directions.
 */
class InvalidDirectionException : public PoneException {
  public:
    /**
     * Default InvalidDirectionException constructor.
     *
     * @warning This constructor is deleted.
     */
    InvalidDirectionException() = delete;

    /**
     * Constructs an InvalidDirectionException with an ErrorMessage
     * instance.
     *
     * @param msg an ErrorMessage instance.
     */
    InvalidDirectionException(const ErrorMessage &msg)
        : PoneException("InvalidDirectionException", msg) {}
};

/**
 * Exception class for invalid numeric values.
 */
class InvalidValueException : public PoneException {
  public:
    /**
     * Default InvalidValueException constructor.
     *
     * @warning This constructor is deleted.
     */
    InvalidValueException() = delete;

    /**
     * Constructs an InvalidValueException with an ErrorMessage
     * instance.
     *
     * @param msg an ErrorMessage instance.
     */
    InvalidValueException(const ErrorMessage &msg)
        : PoneException("InvalidValueException", msg) {}
};

} // namespace pone

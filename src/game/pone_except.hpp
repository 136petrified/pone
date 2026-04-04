/*   Created:  2024-09-08
 *   Modified: 2026-04-03
 */

#pragma once

#include <memory>
#include "pone_gate.hpp"
#include "pone_tile.hpp"
#include "utils/except.h"

namespace pone {

using GatePtr = std::shared_ptr<Gate>;
using TilePtr = std::shared_ptr<Tile>;

/**
 * Default filename for error output.
 */
constexpr std::string ERR_FILE = "./errlog.txt";

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
class DuplicateTileCoordinatesException : public PoneException {
   public:
    DuplicateTileCoordinatesException() = delete;

    DuplicateTileCoordinatesException(const ErrorMessage &msg)
        : PoneException("DuplicateTileCoordinatesException", msg) {}
};

class DuplicateTileNamesException : public PoneException {
   public:
    DuplicateTileNamesException() = delete;

    DuplicateTileNamesException(const ErrorMessage &msg)
        : PoneException("DuplicateTileNamesException", msg) {}
};

class TileNotFoundException : public PoneException {
   public:
    TileNotFoundException() = delete;

    TileNotFoundException(const ErrorMessage &msg)
        : PoneException("TileNotFoundException", msg) {}
};

class DuplicateGateTilesException : public PoneException {
   public:
    DuplicateGateTilesException() = delete;

    DuplicateGateTilesException(const ErrorMessage &msg)
        : PoneException("DuplicateGateTilesException", msg) {}
};

class DuplicateGateNamesException : public PoneException {
   public:
    DuplicateGateNamesException() = delete;

    DuplicateGateNamesException(const ErrorMessage &msg)
        : PoneException("DuplicateGateNamesException", msg) {}
};

class GateCollisionException : public PoneException {
   public:
    GateCollisionException() = delete;

    GateCollisionException(const ErrorMessage &msg)
        : PoneException("GateCollisionException", msg) {}
};

class GateEmptyException : public PoneException {
   public:
    GateEmptyException() = delete;

    GateEmptyException(const ErrorMessage &msg)
        : PoneException("GateEmptyException", msg) {}
};

class GateNotFoundException : public PoneException {
   public:
    GateNotFoundException() = delete;

    GateNotFoundException(const ErrorMessage &msg)
        : PoneException("GateNotFoundException", msg) {}
};

class GoalNotFoundException : public PoneException {
   public:
    GoalNotFoundException() = delete;

    GoalNotFoundException(const ErrorMessage &msg)
        : PoneException("GoalNotFoundException", msg) {}
};

class InvalidTileException : public PoneException {
   public:
    InvalidTileException() = delete;

    InvalidTileException(const ErrorMessage &msg)
        : PoneException("InvalidTileException", msg) {}
};

class NotANumberException : public PoneException {
   public:
    NotANumberException() = delete;

    NotANumberException(const ErrorMessage &msg)
        : PoneException("NotANumberException", msg) {}
};

class InvalidDirectionException : public PoneException {
   public:
    InvalidDirectionException() = delete;

    InvalidDirectionException(const ErrorMessage &msg)
        : PoneException("InvalidDirectionException", msg) {}
};

class InvalidValueException : public PoneException {
   public:
    InvalidValueException() = delete;

    InvalidValueException(const ErrorMessage &msg)
        : PoneException("InvalidValueException", msg) {}
};

}  // namespace pone

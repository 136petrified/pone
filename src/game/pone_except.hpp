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
 * Abstract exception class for tiles.
 */
class TileException : public std::runtime_error {
   protected:
    std::string m_name;
    ErrorMessage m_msg;

   public:
    /**
     * Default TileException constructor.
     *
     * @warning This constructor is deleted.
     */
    TileException() = delete;

    /**
     * Constructs a TileException with the exception name and message.
     *
     * @param name of the exception.
     * @param msg the error message.
     */
    TileException(const std::string &name, const ErrorMessage &msg)
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
class DuplicateTileCoordinatesException : public TileException {
   public:
    DuplicateTileCoordinatesException() = delete;

    DuplicateTileCoordinatesException(const ErrorMessage &msg)
        : TileException("DuplicateTileCoordinatesException", msg) {}
};

class DuplicateTileNamesException : public TileException {
   public:
    DuplicateTileNamesException() = delete;

    DuplicateTileNamesException(const ErrorMessage &msg)
        : TileException("DuplicateTileNamesException", msg) {}
};

class TileNotFoundException : public TileException {
   public:
    TileNotFoundException() = delete;

    TileNotFoundException(const ErrorMessage &msg)
        : TileException("TileNotFoundException", msg) {}
};

class GateException : public std::runtime_error {
   protected:
    std::string m_name;
    ErrorMessage m_msg;

   public:
    GateException() = delete;
    GateException(const std::string &name, const ErrorMessage &msg)
        : std::runtime_error(msg.toString()), m_name{name}, m_msg{msg} {}
    std::string toString() const;
    void logToFile(const std::string &file_name) const;
};

class DuplicateGateTilesException : public GateException {
   public:
    DuplicateGateTilesException() = delete;

    DuplicateGateTilesException(const ErrorMessage &msg)
        : GateException("DuplicateGateTilesException", msg) {}
};

class DuplicateGateNamesException : public GateException {
   public:
    DuplicateGateNamesException() = delete;

    DuplicateGateNamesException(const ErrorMessage &msg)
        : GateException("DuplicateGateNamesException", msg) {}
};

class GateCollisionException : public GateException {
   public:
    GateCollisionException() = delete;

    GateCollisionException(const ErrorMessage &msg)
        : GateException("GateCollisionException", msg) {}
};

class GateEmptyException : public GateException {
   public:
    GateEmptyException() = delete;

    GateEmptyException(const ErrorMessage &msg)
        : GateException("GateEmptyException", msg) {}
};

class GateNotFoundException : public GateException {
   public:
    GateNotFoundException() = delete;

    GateNotFoundException(const ErrorMessage &msg)
        : GateException("GateNotFoundException", msg) {}
};

class BoardException : public std::runtime_error {
   protected:
    std::string m_name;
    ErrorMessage m_msg;

   public:
    BoardException() = delete;
    BoardException(const std::string &name, const ErrorMessage &msg)
        : std::runtime_error(msg.toString()), m_name{name}, m_msg{msg} {}
    std::string toString() const;
    void logToFile(const std::string &file_name) const;
};

class GoalNotFoundException : public BoardException {
   public:
    GoalNotFoundException() = delete;

    GoalNotFoundException(const ErrorMessage &msg)
        : BoardException("GoalNotFoundException", msg) {}
};

class GameException : public std::runtime_error {
   protected:
    std::string m_name;
    ErrorMessage m_msg;

   public:
    GameException() = delete;
    GameException(const std::string &name, const ErrorMessage &msg)
        : std::runtime_error(msg.toString()), m_name{name}, m_msg{msg} {}
    std::string toString() const;
    void logToFile() const;
};

class InvalidTileException : public GameException {
   public:
    InvalidTileException() = delete;

    InvalidTileException(const ErrorMessage &msg)
        : GameException("InvalidTileException", msg) {}
};

class NotANumberException : public GameException {
   public:
    NotANumberException() = delete;

    NotANumberException(const ErrorMessage &msg)
        : GameException("NotANumberException", msg) {}
};

class InvalidDirectionException : public GameException {
   public:
    InvalidDirectionException() = delete;

    InvalidDirectionException(const ErrorMessage &msg)
        : GameException("InvalidDirectionException", msg) {}
};

class InvalidValueException : public GameException {
   public:
    InvalidValueException() = delete;

    InvalidValueException(const ErrorMessage &msg)
        : GameException("InvalidValueException", msg) {}
};

}  // namespace pone

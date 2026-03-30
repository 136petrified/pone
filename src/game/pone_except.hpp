/*   Created:  2024-09-08
 *   Modified: 2026-03-04
 */

#pragma once

#include <format>
#include <fstream>
#include <memory>
#include "pone_board.hpp"
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
        : std::runtime_error(msg.getString()), m_name{name}, m_msg{msg} {}

    /**
     * Virtual function for getting a formatted
     * error message.
     *
     * @returns the error message.
     */
    virtual std::string getString() const = 0;

    /**
     * Pure virtual function for logging the error message into the
     * specified file.
     *
     * @param file_name filename to log the error to.
     */
    virtual void logToFile(const std::string &file_name) const = 0;
};

/**
 * Exception class for duplicate tiles.
 */
class DuplicateTileCoordinatesException : public TileException {
    std::string m_msg;

   public:
    DuplicateTileCoordinatesException() = delete;

    DuplicateTileCoordinatesException(const int &x, const int &y)
        : TileException("DuplicateTileCoordinatesException", makeMessage(x, y)),
          m_msg{makeMessage(x, y)} {}

    std::string getString() const override {
        return "";
    }

    void logToFile(const std::string &file_name) const override {
        std::ofstream ofs{file_name, std::ios::app};
        ofs << m_msg.getString() << '\n';
        ofs.close();
    }
};

class DuplicateTileNamesException : public TileException {
   public:
    DuplicateTileNamesException() = delete;

    DuplicateTileNamesException(const std::string &name)
        : TileException("DuplicateTileNamesException", makeMessage(name)),
          m_msg{makeMessage(name)} {}

   private:
    std::string makeMessage(const std::string &name) const {
        return std::format(
            "Multiple tiles with duplicate names detected with the name {}",
            name);
    }

    std::string m_msg;
};

class TileNotFoundException : public TileException {
    std::string makeMessage() const {
        return "Null Tile (a nonexistent Tile) has been passed as an argument!";
    }

    std::string makeMessage(const std::string &tile_name) const {
        return std::format("Tile \"{}\" was not found!", tile_name);
    }

    std::string makeMessage(const int &x, const int &y) const {
        return std::format("Tile with coordinates ({}, {}) was not found!", x,
                           y);
    }

    std::string m_msg;

   public:
    TileNotFoundException()
        : TileException("TileNotFoundException", makeMessage()),
          m_msg{makeMessage()} {}

    TileNotFoundException(const std::string &tile_name)
        : TileException("TileNotFoundException", makeMessage(tile_name)),
          m_msg{makeMessage()} {}

    TileNotFoundException(const int &x, const int &y)
        : TileException("TileNotFoundException", makeMessage(x, y)),
          m_msg{makeMessage(x, y)} {}

    const std::string &getMessage() const override {
        return m_msg;
    }

    void logToFile(const std::string &file_name) const override {
        std::ofstream ofs{file_name, std::ios::app};
        ofs << m_msg << '\n';
        ofs.close();
    }
};

class GateException : public std::runtime_error {
    std::string m_name;

   public:
    GateException() = delete;
    GateException(const std::string &name, const std::string &msg)
        : std::runtime_error(msg), m_name{name} {}
    virtual const std::string &getMessage() const              = 0;
    virtual void logToFile(const std::string &file_name) const = 0;
};

class DuplicateGateTilesException : public GateException {
    std::string makeMessage(const TilePtr &tptr1, const TilePtr &tptr2) {
        if (tptr1 == nullptr || tptr2 == nullptr) {
            return "Null Tile pointers passed to this exception.";
        }

        return std::format(
            "Multiple gates with duplicate tiles "
            "detected with the tiles: x: "
            "{}, y: {}",
            tptr1->getName(), tptr2->getName());
    }

    std::string m_msg;

   public:
    DuplicateGateTilesException() = delete;

    DuplicateGateTilesException(const TilePtr &tptr1, const TilePtr &tptr2)
        : GateException("DuplicateGateTilesException",
                        makeMessage(tptr1, tptr2)),
          m_msg{makeMessage(tptr1, tptr2)} {}
};

class DuplicateGateNamesException : public GateException {
   public:
    DuplicateGateNamesException() = delete;

    DuplicateGateNamesException(const std::string &name)
        : GateException("DuplicateGateNamesException", makeMessage(name)),
          m_msg{makeMessage(name)} {}

    const std::string &getMessage() const override {
        return m_msg;
    }

    void logToFile(const std::string &file_name) const override {
        std::ofstream ofs{file_name, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage(const std::string &name) const {
        return std::format(
            "Multiple gates with duplicate names "
            "detected with the name: {}",
            name);
    }

    std::string m_msg;
};

class GateCollisionException : public GateException {
   public:
    GateCollisionException() = delete;

    GateCollisionException(const TilePtr &tptr)
        : GateException("GateCollisionException", makeMessage(tptr)),
          m_msg{makeMessage(tptr)} {}

    const std::string &getMessage() const override {
        return m_msg;
    }

    void logToFile(const std::string &file_name) const override {
        std::ofstream ofs{file_name, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage(const TilePtr &tptr) const {
        return std::format(
            "Attempted to create a gate with a collision tile: {}",
            tptr->getName());
    }

    std::string m_msg;
};

class GateEmptyException : public GateException {
   public:
    GateEmptyException() = delete;

    GateEmptyException(const GatePtr &gptr)
        : GateException("GateEmptyException", makeMessage(gptr)),
          m_msg{makeMessage(gptr)} {}

    const std::string &getMessage() const override {
        return m_msg;
    }

    void logToFile(const std::string &file_name) const override {
        std::ofstream ofs{file_name, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage(const GatePtr &gptr) const {
        if (gptr == nullptr) {
            return "Null Gate pointer was passed to this exception.";
        }

        return std::format("Gate {} has no tiles to remove!", gptr->getName());
    }
    std::string m_msg;
};

class GateNotFoundException : public GateException {
   public:
    GateNotFoundException()
        : GateException("GateNotFoundException", makeMessage()),
          m_msg{makeMessage()} {}

    GateNotFoundException(const std::string &name)
        : GateException("GateNotFoundException", makeMessage(name)),
          m_msg{makeMessage(name)} {}

    GateNotFoundException(const TilePair &tp)
        : GateException("GateNotFoundException", makeMessage(tp)),
          m_msg{makeMessage(tp)} {}

    const std::string &getMessage() const override {
        return m_msg;
    }

    void logToFile(const std::string &file_name) const override {
        std::ofstream ofs{file_name, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const {
        return "A Null Gate (a nonexistent Gate) was "
               "passed as an argument!";
    }

    std::string makeMessage(const std::string &name) const {
        return std::format("Gate \"{}\" was not found!", name);
    }

    std::string makeMessage(const TilePair &tp) const {
        return std::format(
            "Gate with Tiles "
            "\"{}\" and \"{}\" was not "
            "found!",
            tp.first->getName(), tp.second->getName());
    }

    std::string m_msg;
};

class BoardException : public std::runtime_error {
   public:
    BoardException() = delete;
    BoardException(const std::string &name, const std::string &msg)
        : std::runtime_error(msg), m_name{name} {}
    virtual const std::string &getMessage() const              = 0;
    virtual void logToFile(const std::string &file_name) const = 0;

   protected:
    std::string m_name;
};

class GoalNotFoundException : public BoardException {
   public:
    GoalNotFoundException() = delete;

    GoalNotFoundException(const Board &b)
        : BoardException("GoalNotFoundException", makeMessage(b)),
          m_msg{makeMessage(b)} {}

    const std::string &getMessage() const {
        return m_msg;
    }

    void logToFile(const std::string &file_name) const {
        std::ofstream ofs{file_name, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage(const Board &b) const {
        return std::format(
            "GoalNotFoundException: No Tile with type \"goal\" found in "
            "Board \"{}\"! A Tile with type \"goal\" is required inside of a "
            "Board with more than 1 Tile!",
            b.getName());
    }

    std::string m_msg;
};

class GameException : public std::runtime_error {
   public:
    GameException() = delete;
    GameException(const std::string &name, const std::string &msg)
        : std::runtime_error(msg), m_name{name} {}
    virtual const std::string &getMessage() const = 0;
    virtual void logToFile() const                = 0;

   protected:
    std::string m_name;
};

class InvalidTileException : public GameException {
   public:
    InvalidTileException()
        : GameException("InvalidTileException", makeMessage()),
          m_msg{makeMessage()} {}

    InvalidTileException(const std::string &name)
        : GameException("InvalidTileException", makeMessage()),
          m_msg{makeMessage(name)} {}

    // Assume gptr is not nullptr; check is done before
    // calling constructor.

    InvalidTileException(const TilePtr &tptr, const GatePtr &gptr)
        : GameException("InvalidTileException", makeMessage(tptr, gptr)),
          m_msg{makeMessage(tptr, gptr)} {}

    const std::string &getMessage() const {
        return m_msg;
    }

    void logToFile(const std::string &file_name) const {
        std::ofstream ofs{file_name, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const {
        return "Null Tile (a nonexistent Tile) is passed as an argument!";
    }

    std::string makeMessage(const std::string &name) {
        return std::format(
            "Null Tile (a nonexistent Tile) is passed as a argument to {}!",
            name);
    }

    std::string makeMessage(const TilePtr &tptr, const GatePtr &gptr) {
        return (tptr == nullptr) ? std::format(
                                       "Null Tile (a nonexistent Tile "
                                       "object) is within the Gate \"{}\"",
                                       gptr->getName())
                                 : std::format(
                                       "Invalid Tile \"{}\" within "
                                       "Gate "
                                       "\"{}\"",
                                       tptr->getName(), gptr->getName());
    }

    std::string m_msg;
};

class NotANumberException : public GameException {
   public:
    NotANumberException() = delete;

    NotANumberException(const std::string &msg)
        : GameException("NotANumberException", msg), m_msg{msg} {}

    const std::string &getMessage() const {
        return m_msg;
    }

    void logToFile(const std::string &file_name) const {
        std::ofstream ofs{file_name, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string m_msg;
};

class InvalidDirectionException : public GameException {
   public:
    InvalidDirectionException()
        : GameException("InvalidDirectionException", makeMessage()),
          m_msg{makeMessage()} {}

    const std::string &getMessage() const {
        return m_msg;
    }

    void logToFile(const std::string &file_name) const {
        std::ofstream ofs{file_name, std::ios::app};
        ofs << m_name << ": " << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const {
        return "Invalid direction!";
    }

    std::string m_msg;
};

class InvalidValueException : public GameException {
   public:
    InvalidValueException() = delete;

    InvalidValueException(const std::string &msg)
        : GameException("InvalidValueException", msg), m_msg{msg} {}

    InvalidValueException(const int &value, const std::string &msg)
        : GameException("InvalidValueException", makeMessage(value, msg)),
          m_msg{makeMessage(value, msg)} {}

    const std::string &getMessage() const {
        return m_msg;
    }

    void logToFile(const std::string &file_name) const {
        std::ofstream ofs{file_name, std::ios::app};
        ofs << m_msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage(const int &value, const std::string msg) {
        return std::format("{} : {}", value, msg);
    }
    std::string m_msg;
};

}  // namespace pone

/*   Created:  09-08-2024
 *   Modified: 07-16-2025
 */

#ifndef PONE_EXCEPTION_HPP
#define PONE_EXCEPTION_HPP

#include <format>
#include <fstream>
#include <memory>

#include "poneboard.hpp"
#include "ponegate.hpp"
#include "ponetile.hpp"

using GatePtr = std::shared_ptr<Gate>;
using TilePtr = std::shared_ptr<Tile>;

constexpr std::string ERR_FILE = "./errlog.txt";

// TODO: Include exception name into exceptions for all exceptions
// TODO: Create a function in each exception to log the exception into a file!

void logToFile(const std::string &msg);

class TileException : public std::exception {
    // This class is an ABSTRACT BASE CLASS! Do not set any values to it.
   public:
    TileException() = delete;
    TileException(const std::string &name) : name{name} {}
    virtual const char *what() const noexcept override = 0;

   private:
    std::string name;
};

class DuplicateTileCoordinatesException : public TileException {
   public:
    DuplicateTileCoordinatesException() = delete;
    DuplicateTileCoordinatesException(const int &x, const int &y)
        : TileException("DuplicateTileCoordinatesException") {
        msg = std::format(
            "Multiple tiles with duplicate coordinates detected with the "
            "coordinates: x: {}, y: {}",
            x, y);
    }
    const char *what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
};

class DuplicateTileNamesException : public TileException {
   public:
    DuplicateTileNamesException() = delete;
    DuplicateTileNamesException(const std::string &name)
        : TileException("DuplicateTileNamesException") {
        msg = std::format(
            "Multiple tiles with duplicate names detected with the name {}",
            name);
    }
    const char *what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
};

class TileNotFoundException : public TileException {
   public:
    TileNotFoundException() = delete;
    TileNotFoundException(const std::string &tile_name)
        : TileException("TileNotFoundException") {
        msg = std::format("TileNotFoundException: Tile \"{}\" was not found!",
                          tile_name);
    }
    TileNotFoundException(const int &x, const int &y)
        : TileException("TileNotFoundException") {
        msg = std::format(
            "TileNotFoundException: Tile with coordinates ({}, {}) was not "
            "found!",
            x, y);
    }
    const char *what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
};

// TODO: You cannot have a board without a goal

class GateException : public std::exception {
   public:
    GateException() = delete;
    GateException(const std::string &name) : name{name} {}
    virtual const char *what() const noexcept override = 0;

   private:
    std::string name;
};

class DuplicateGateTilesException : public GateException {
   public:
    DuplicateGateTilesException() = delete;
    DuplicateGateTilesException(TilePtr tptr1, TilePtr tptr2)
        : GateException("DuplicateGateTilesException") {
        msg = std::format(
            "Multiple gates with duplicate tiles detected with the tiles: x: "
            "{}, y: {}",
            tptr1->getName(), tptr2->getName());
    }
    const char *what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
};

class DuplicateGateNamesException : public GateException {
   public:
    DuplicateGateNamesException() = delete;
    DuplicateGateNamesException(const std::string &name)
        : GateException("DuplicateGateNamesException") {
        msg = std::format(
            "Multiple gates with duplicate names detected with the name: {}",
            name);
    }
    const char *what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
};

class GateCollisionException : public GateException {
   public:
    GateCollisionException() = delete;
    GateCollisionException(TilePtr tptr)
        : GateException("GateCollisionException") {
        msg =
            std::format("Attempted to create a gate with a collision tile: {}",
                        tptr->getName());
    }
    const char *what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
};

class GateEmptyException : public GateException {
   public:
    GateEmptyException() = delete;
    GateEmptyException(GatePtr gptr) : GateException("GateEmptyException") {
        msg = std::format("Gate {} has no tiles to remove!", gptr->getName());
    }
    const char *what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
};

class InvalidTileException : std::exception {
   public:
    InvalidTileException()
        : msg{"InvalidTileException: Null Tile (a nonexistent Tile) is passed "
              "as a argument!"} {}
    InvalidTileException(const std::string &to_where)
        : msg{std::format(
              "InvalidTileException: Null Tile (a nonexistent Tile) is passed "
              "as a argument to {}!",
              to_where)} {}
    InvalidTileException(TilePtr tptr, GatePtr gptr) {
        // Assume gptr is never nullptr

        msg = (tptr == nullptr)
                  ? std::format(
                        "InvalidTileException: Null Tile (a nonexistent Tile "
                        "object) is within the Gate \"{}\"",
                        gptr->getName())
                  : std::format(
                        "InvalidTileException: Invalid Tile \"{}\" within Gate "
                        "\"{}\"",
                        tptr->getName(), gptr->getName());
    }
    const char *what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
};

class NotANumberException : public std::exception {
   public:
    NotANumberException() = delete;
    NotANumberException(const std::string &msg) : msg{msg} {}
    const char *what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
};

class InvalidDirectionException : public std::exception {
   public:
    InvalidDirectionException() : msg{"Invalid direction!"} {}
    const char *what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
};

class InvalidValueException : public std::exception {
   public:
    InvalidValueException() = delete;
    InvalidValueException(const std::string &msg) : msg{msg} {}
    InvalidValueException(const int &value, const std::string &msg) {
        this->msg = std::format("{} : {}", value, msg);
    }
    const char *what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
};

class BoardException : public std::exception {
   public:
    BoardException() = delete;
    BoardException(const std::string &name) : name{name} {}
    virtual const char *what() const noexcept override = 0;

   private:
    std::string name;
};

class GoalNotFoundException : public BoardException {
   public:
    GoalNotFoundException() = delete;
    GoalNotFoundException(const Board &b)
        : BoardException("GoalNotFoundException") {
        msg = std::format(
            "GoalNotFoundException: No Tile with type \"goal\" found in Board "
            "\"{}\"! A Tile with type \"goal\" is required inside of a Board "
            "with more than 1 Tile!",
            b.getName());
    }

   private:
    std::string msg;
};

#endif  // PONE_EXCEPTION_HPP

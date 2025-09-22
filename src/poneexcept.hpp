/*   Created:  09-08-2024
 *   Modified: 09-22-2025
 */

#ifndef PONE_EXCEPTION_HPP
#define PONE_EXCEPTION_HPP

#include <format>
#include <fstream>
#include <memory>

#include "poneboard.hpp"
#include "ponegate.hpp"
#include "ponetile.hpp"

// TODO: Complete makeMessage implementations

using GatePtr = std::shared_ptr<Gate>;
using TilePtr = std::shared_ptr<Tile>;

constexpr std::string ERR_FILE = "./errlog.txt";

class TileException : public std::runtime_error {
    // This class is an ABSTRACT BASE CLASS! Do not set any values to it.
   public:
    TileException() = delete;
    TileException(const std::string &name, const std::string &msg)
        : std::runtime_error(msg), m_Name{name} {}
    virtual const std::string &getMessage() const = 0;
    virtual void logToFile() const = 0;

   private:
    std::string m_Name;
};

class DuplicateTileCoordinatesException : public TileException {
   public:
    DuplicateTileCoordinatesException() = delete;

    DuplicateTileCoordinatesException(const int &x, const int &y)
        : TileException("DuplicateTileCoordinatesException", makeMessage(x, y)),
          m_Msg{makeMessage(x, y)} {}

    const std::string &getMessage() const override { return m_Msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage(const int &x, const int &y) const {
        return std::format(
            "Multiple tiles with duplicate coordinates detect with the "
            "coordinates: x: {}, y: {}",
            x, y);
    }

    std::string m_Msg;
};

class DuplicateTileNamesException : public TileException {
   public:
    DuplicateTileNamesException() = delete;

    DuplicateTileNamesException(const std::string &name)
        : TileException("DuplicateTileNamesException", makeMessage(name)),
          m_Msg{makeMessage(name)} {}

   private:
    std::string makeMessage(const std::string &name) const {
        return std::format(
            "Multiple tiles with duplicate names detected with the name {}",
            name);
    }

    std::string m_Msg;
};

class TileNotFoundException : public TileException {
   public:
    TileNotFoundException()
        : TileException("TileNotFoundException", makeMessage()),
          m_Msg{makeMessage()} {}

    TileNotFoundException(const std::string &tileName)
        : TileException("TileNotFoundException", makeMessage(tileName)),
          m_Msg{makeMessage()} {}

    TileNotFoundException(const int &x, const int &y)
        : TileException("TileNotFoundException", makeMessage(x, y)),
          m_Msg{makeMessage(x, y)} {}

    const std::string &getMessage() const override { return m_Msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage() const {
        return "Null Tile (a nonexistent Tile) has been passed as an argument!";
    }

    std::string makeMessage(const std::string &tileName) const {
        return std::format("Tile \"{}\" was not found!", tileName);
    }

    std::string makeMessage(const int &x, const int &y) const {
        return std::format("Tile with coordinates ({}, {}) was not found!", x,
                           y);
    }

    std::string m_Msg;
};

class GateException : public std::runtime_error {
   public:
    GateException() = delete;
    GateException(const std::string &name, const std::string &msg)
        : std::runtime_error(msg), m_Name{name} {}
    virtual const std::string &getMessage() const = 0;
    virtual void logToFile() const = 0;

   private:
    std::string m_Name;
};

class DuplicateGateTilesException : public GateException {
   public:
    DuplicateGateTilesException() = delete;

    DuplicateGateTilesException(const TilePtr &tptr1, const TilePtr &tptr2)
        : GateException("DuplicateGateTilesException",
                        makeMessage(tptr1, tptr2)),
          m_Msg{makeMessage(tptr1, tptr2)} {}

   private:
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
    std::string m_Msg;
};

class DuplicateGateNamesException : public GateException {
   public:
    DuplicateGateNamesException() = delete;

    DuplicateGateNamesException(const std::string &name)
        : GateException("DuplicateGateNamesException", makeMessage(name)),
          m_Msg{makeMessage(name)} {}

    const std::string &getMessage() const override { return m_Msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage(const std::string &name) const {
        return std::format(
            "Multiple gates with duplicate names "
            "detected with the name: {}",
            name);
    }

    std::string m_Msg;
};

class GateCollisionException : public GateException {
   public:
    GateCollisionException() = delete;

    GateCollisionException(const TilePtr &tptr)
        : GateException("GateCollisionException", makeMessage(tptr)),
          m_Msg{makeMessage(tptr)} {}

    const std::string &getMessage() const override { return m_Msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string makeMessage(const TilePtr &tptr) const {
        return std::format(
            "Attempted to create a gate with a collision tile: {}",
            tptr->getName());
    }

    std::string m_Msg;
};

class GateEmptyException : public GateException {
   public:
    GateEmptyException() = delete;

    GateEmptyException(const GatePtr &gptr)
        : GateException(
              "GateEmptyException",
              std::format("Gate {} has no tiles to remove!", gptr->getName())),
          m_Msg{std::format("Gate {} has no tiles to remove!",
                            gptr->getName())} {}

    const std::string &getMessage() const override { return m_Msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string m_Msg;
};

class GateNotFoundException : public GateException {
   public:
    GateNotFoundException()
        : GateException("GateNotFoundException",
                        "A Null Gate (a nonexistent Gate) was "
                        "passed as an argument!"),
          m_Msg{
              "A Null Gate (a nonexistent Gate) was "
              "passed as an argument!"} {}

    GateNotFoundException(const std::string &gate_name)
        : GateException("GateNotFoundException",
                        std::format("Gate \"{}\" was not found!", gate_name)),
          m_Msg{std::format("Gate \"{}\" was not found!", gate_name)} {}

    GateNotFoundException(const TilePair &tp)
        : GateException("GateNotFoundException",
                        std::format("Gate with Tiles "
                                    "\"{}\" and \"{}\" was not "
                                    "found!",
                                    tp.first->getName(), tp.second->getName())),
          m_Msg{std::format("Gate with Tiles \"{}\" and "
                            "\"{}\" was not "
                            "found!",
                            tp.first->getName(), tp.second->getName())} {}

    const std::string &getMessage() const override { return m_Msg; }

    void logToFile() const override {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string m_Msg;
};

class BoardException : public std::runtime_error {
   public:
    BoardException() = delete;
    BoardException(const std::string &name, const std::string &msg)
        : std::runtime_error(msg), m_Name{name} {}
    virtual const std::string &getMessage() const = 0;
    virtual void logToFile() const = 0;

   private:
    std::string m_Name;
};

class GoalNotFoundException : public BoardException {
   public:
    GoalNotFoundException() = delete;

    GoalNotFoundException(const Board &b)
        : BoardException(
              "GoalNotFoundException",
              std::format(
                  "GoalNotFoundException: No Tile with type \"goal\" found in "
                  "Board "
                  "\"{}\"! A Tile with type \"goal\" is required inside of a "
                  "Board "
                  "with more than 1 Tile!",
                  b.getName())),
          m_Msg{std::format(
              "GoalNotFoundException: No Tile with type \"goal\" found in "
              "Board "
              "\"{}\"! A Tile with type \"goal\" is required inside of a "
              "Board "
              "with more than 1 Tile!",
              b.getName())} {}

    const std::string &getMessage() const { return m_Msg; }

    void logToFile() const {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string m_Msg;
};

class InvalidTileException : public std::runtime_error {
   public:
    InvalidTileException()
        : std::runtime_error(
              "Null Tile (a nonexistent Tile) is "
              "passed "
              "as a argument!"),
          m_Msg{
              "Null Tile (a nonexistent Tile) is "
              "passed "
              "as a argument!"} {}

    InvalidTileException(const std::string &toWhere)
        : std::runtime_error(std::format("Null Tile (a nonexistent "
                                         "Tile) is passed "
                                         "as a argument to {}!",
                                         toWhere)),
          m_Msg{std::format("Null Tile (a nonexistent "
                            "Tile) is passed "
                            "as a argument to {}!",
                            toWhere)} {}

    // Assume gptr is not nullptr; check is done before
    // calling constructor.

    InvalidTileException(const TilePtr &tptr, const GatePtr &gptr)
        : std::runtime_error(
              (tptr == nullptr)
                  ? std::format("Null Tile (a nonexistent Tile "
                                "object) is within the Gate \"{}\"",
                                gptr->getName())
                  : std::format("Invalid Tile \"{}\" within "
                                "Gate "
                                "\"{}\"",
                                tptr->getName(), gptr->getName())),
          m_Msg{(tptr == nullptr)
                    ? std::format("Null Tile (a nonexistent Tile "
                                  "object) is within the Gate \"{}\"",
                                  gptr->getName())
                    : std::format("Invalid Tile \"{}\" within "
                                  "Gate "
                                  "\"{}\"",
                                  tptr->getName(), gptr->getName())} {}

    const std::string &getMessage() const { return m_Msg; }

    void logToFile() const {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string m_Msg;
};

class NotANumberException : public std::runtime_error {
   public:
    NotANumberException() = delete;

    NotANumberException(const std::string &msg)
        : std::runtime_error(msg), m_Msg{msg} {}

    const std::string &getMessage() const { return m_Msg; }

    void logToFile() const {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string m_Msg;
};

class InvalidDirectionException : public std::runtime_error {
   public:
    InvalidDirectionException()
        : std::runtime_error("Invalid direction!"),
          m_Msg{"Invalid direction!"} {}

    const std::string &getMessage() const { return m_Msg; }

    void logToFile() const {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string m_Msg;
};

class InvalidValueException : public std::runtime_error {
   public:
    InvalidValueException() = delete;

    InvalidValueException(const std::string &msg)
        : std::runtime_error(msg), m_Msg{msg} {}

    InvalidValueException(const int &value, const std::string &msg)
        : std::runtime_error(std::format("{} : {}", value, msg)),
          m_Msg{std::format("{} : {}", value, msg)} {}

    const std::string &getMessage() const { return m_Msg; }

    void logToFile() const {
        std::ofstream ofs{ERR_FILE, std::ios::app};
        ofs << m_Msg << '\n';
        ofs.close();
    }

   private:
    std::string m_Msg;
};

#endif  // PONE_EXCEPTION_HPP

/*   Created:  09-08-2024
 *   Modified: 06-29-2025
 */

#ifndef PONE_EXCEPTION_HPP
#define PONE_EXCEPTION_HPP

#include <format>

#include "ponegate.hpp"
#include "ponetile.hpp"

constexpr std::string ERR_FILE = "./errlog.txt";

// #define ERR_MSG_LIMIT 150                           // Max char limit for
// buffered error messages
// TODO: Maybe use custom exception

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
        msg = std::format("Tile {} was not found!", tile_name);
    }
    const char *what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
};

// TODO: Convert these exceptions to virtual excpetion classes

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
    DuplicateGateTilesException(Tile *t1, Tile *t2)
        : GateException("DuplicateGateTilesException") {
        msg = std::format(
            "Multiple gates with duplicate tiles detected with the tiles: x: "
            "{}, y: {}",
            t1->getName(), t2->getName());
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
    GateCollisionException(Tile *t) : GateException("GateCollisionException") {
        msg =
            std::format("Attempted to create a gate with a collision tile: {}",
                        t->getName());
    }
    const char *what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
};

class GateEmptyException : public GateException {
   public:
    GateEmptyException() = delete;
    GateEmptyException(Gate *g) : GateException("GateEmptyException") {
        msg = std::format("Gate {} has no tiles to remove!", g->getName());
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

#endif  // PONE_EXCEPTION_HPP

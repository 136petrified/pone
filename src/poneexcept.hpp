/*  Created:  SEP  8 2024
*   Modified: FEB 18 2025
*/

#ifndef PONE_EXCEPTION_HPP
#define PONE_EXCEPTION_HPP

#include <cstdio>
#include <format>
#include <stdexcept>

// #define ERR_MSG_LIMIT 150                           // Max char limit for buffered error messages

class TileException : public std::exception {
// This class is an ABSTRACT BASE CLASS! Do not set any values to it.
public:
    TileException() = default;
    virtual const char *what() const noexcept override = 0;
};

class DuplicateTileCoordinatesException : public TileException {
public:
    DuplicateTileCoordinatesException() = delete;
    DuplicateTileCoordinatesException(const int &x, const int& y) {
        msg = std::format("Multiple tiles with duplicate coordinates detected with the coordinates: x: {}, y: {}", x, y);
    }
    const char *what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class DuplicateTileNamesException : public TileException {
public:
    DuplicateTileNamesException() = delete;
    DuplicateTileNamesException(const std::string &name) {
        msg = std::format("Multiple tiles with duplicate names detected with the name {}", name);
    }
    const char *what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class TileNotFoundException : public TileException {
public:
    TileNotFoundException() = delete;
    TileNotFoundException(const std::string &msg) : msg{msg} {}
    const char *what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

// TODO: Convert these exceptions to virtual excpetion classes

class GateException : public std::exception {
public:
    GateException() = default;
    virtual const char *what() const noexcept override = 0;
};

class DuplicateGateTilesException : public GateException {
public:
    DuplicateGateTilesException() = delete;
    DuplicateGateTilesException(const Tile *t1, const Tile *t2) {
        msg = std::format("Multiple gates with duplicate tiles detected with the tiles: x: {}, y: {}",
        t1->getName(), t2->getName());
    }
    const char *what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};


class DuplicateGateNamesException : public GateException {
public:
    DuplicateGateNamesException() = delete;
    DuplicateGateNamesException(const std::string &name) {
        msg = std::format("Multiple gates with duplicate names detected with the name: {}", name);
    }
    const char *what() const noexcept override {
        return msg.c_str();
    }
private:
    std::string msg;
};

class NotANumberException : public std::exception {
public:
    NotANumberException() = delete;
    NotANumberException(const std::string &msg) : msg{msg} {}
    const char *what() const noexcept override {
        return msg.c_str();
    }
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
        const char *what() const noexcept override {
            return msg.c_str();
        }
    private:
        std::string msg;
    };

#endif // PONE_EXCEPTION_HPP
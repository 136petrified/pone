/*  Created:  SEP  8 2024
*   Modified: FEB 12 2025
*/

#ifndef PONE_EXCEPTION_HPP
#define PONE_EXCEPTION_HPP

#include <cstdio>
#include <stdexcept>

#define ERR_MSG_LIMIT 150                           // Max char limit for buffered error messages

class TileException : public std::exception {
// This class is an ABSTRACT BASE CLASS! Do not set any values to it.
public:
    TileException() = default;
    virtual const char *what() const noexcept override = 0;
};

class DuplicateTileCoordinatesException : public TileException {
public:
    DuplicateTileCoordinatesException(const int &x, const int& y) {
        std::sprintf(buf, "Multiple tiles with duplicate coordinates detected with the coordinates: x: %d, y: %d",
        x, y);
    }
    const char *what() const noexcept override {
        return buf;
    }

private:
    char buf[ERR_MSG_LIMIT];
};

class DuplicateTileNamesException : public TileException {
public:
    DuplicateTileNamesException(const std::string &name) {
        std::sprintf(buf, "Multiple tiles with duplicate names detected with the name %s", name.c_str());
    }
    const char *what() const noexcept override {
        return buf;
    }

private:
    char buf[ERR_MSG_LIMIT];
};

class TileNotFoundException : public TileException {
public:
    TileNotFoundException(const char msg[]) : msg{msg} {}
    const char *what() const noexcept override {
        return msg;
    }

private:
    const char *msg;
};

// TODO: Convert these exceptions to virtual excpetion classes

class GateException : public std::exception {
public:
    GateException(const char msg[]) : msg{msg} {}
    const char *what() const noexcept override {
        return msg;
    }

private:
    const char *msg;
};

class DuplicateGateTilesException : public std::exception {
public:
    DuplicateGateTilesException(const Tile *t1, const Tile *t2) {
        std::sprintf(buf, "Multiple gates with duplicate tiles detected with the tiles: x: %s, y: %s",
        t1->getName().c_str(), t2->getName().c_str());
    }
    const char *what() const noexcept override {
        return buf;
    }

private:
    char buf[ERR_MSG_LIMIT];
};


class DuplicateGateNamesException : public std::exception {
public:
    DuplicateGateNamesException(const std::string &name) {
        std::sprintf(buf, "Multiple gates with duplicate names detected with the name: %s", name.c_str());
    }
    const char *what() const noexcept override {
        return buf;
    }
private:
    char buf[ERR_MSG_LIMIT];
};

class NotANumberException : public std::exception {
public:
    NotANumberException(const char msg[]) : msg{msg} {}
    const char *what() const noexcept override {
        return msg;
    }
private:
    const char *msg;
};
#endif // PONE_EXCEPTION_HPP
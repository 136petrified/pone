/*  Created: SEP 8 2024
*   Modified: SEP 8 2024
*/

#ifndef PONE_EXCEPTION_HPP
#define PONE_EXCEPTION_HPP

#include <cstdio>
#include <stdexcept>

#define ERR_MSG_LIMIT 150                           // Max char limit for buffered error messages

class TileException : public std::exception {
public:
    TileException(const char msg[]) : msg{msg} {}
    const char *what() const noexcept override {
        return msg;
    }

private:
    const char *msg;
};

class DuplicateTileCoordinatesException : public std::exception {
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

class DuplicateTileCoordinatesException : public std::exception {
public:
    DuplicateTileCoordinatesException(const std::string& name) {
        std::sprintf(buf, "Multiple tiles with duplicate names detected with the name %s", name.c_str());
    }
    const char *what() const noexcept override {
        return buf;
    }

private:
    char buf[ERR_MSG_LIMIT];
};

class GateException : public std::exception {
public:
    GateException(const char msg[]) : msg{msg} {}
    const char *what() const noexcept override {
        return msg;
    }

private:
    const char *msg;
};

#endif // PONE_EXCEPTION_HPP

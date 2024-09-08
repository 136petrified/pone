/*  Created: SEP 8 2024
*   Modified: SEP 8 2024
*/

#ifndef PONE_EXCEPTION_HPP
#define PONE_EXCEPTION_HPP

#include <stdexcept>

class TileException : public std::exception {
public:
    TileException(const char msg[]) : msg{msg} {}
    const char *what() const noexcept override {
        return msg;
    }

private:
    const char *msg;
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

#include "syntaxerror.hpp"

SyntaxError::SyntaxError(const std::string& str) : _msg(str){}

const std::string& SyntaxError::what() const {
    return _msg;
}

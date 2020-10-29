#include "lexererror.hpp"

LexerError::LexerError(const std::string& str) : _msg(str){}

const std::string& LexerError::what() const {
    return _msg;
}

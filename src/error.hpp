#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <exception>


class LexerError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class SyntaxError  : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class EvalError  : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class NoDefError  : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

#endif // SYNTAXERROR_HPP

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

namespace Operators {
    constexpr char ADD = '+';
    constexpr char MIN = '-';
    constexpr char DIV = '/';
    constexpr char MUL = '*';
    constexpr char SET = '=';
}

namespace BasicCharacters {
    const std::string LPAR = "LPAR";
    const std::string RPAR = "RPAR";
    const std::string PROMPT = "\033[0;32mExpr\033[0;31m>>>\033[0m   ";
    constexpr char LF = '\n';
    constexpr char CR = '\r';
    constexpr char SEMI = ';';
}

enum class TokenType {
    UNARY_OP,
    BINARY_OP,
    ID,
    CONST,
    BASIC
};


#endif // CONSTANTS_HPP

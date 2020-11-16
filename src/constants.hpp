#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <memory>

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
    const std::string COM  = "COMMA";
    const std::string SEMI = "SEMI";
    constexpr char LF = '\n';
    constexpr char CR = '\r';
}

#endif // CONSTANTS_HPP

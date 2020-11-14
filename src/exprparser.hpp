#ifndef EXPRPARSER_H
#define EXPRPARSER_H

#include <vector>
#include <memory>
#include "typealiases.hpp"

class ExprParser {

     public:

        static TokenArray parse(TokenArray& tokens);

};

#endif // EXPRPARSER_H

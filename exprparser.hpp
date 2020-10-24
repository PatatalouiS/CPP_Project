#ifndef EXPRPARSER_H
#define EXPRPARSER_H

#include "token.hpp"
#include <vector>
#include <memory>

class ExprParser {

     public:

        static std::vector<Token*> parse(const std::vector<Token*>& tokens);

};

#endif // EXPRPARSER_H

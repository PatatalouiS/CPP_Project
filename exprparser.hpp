#ifndef EXPRPARSER_H
#define EXPRPARSER_H

#include "evaluabletoken.hpp"
#include <vector>
#include <memory>

class ExprParser {

     public:

        static std::vector<EvaluableToken*> parse(const std::vector<AbstractToken*>& tokens);


};

#endif // EXPRPARSER_H

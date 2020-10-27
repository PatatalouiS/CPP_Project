#ifndef EXPRPARSER_H
#define EXPRPARSER_H

#include "evaluabletoken.hpp"
#include <vector>
#include <memory>
#include "typealiases.hpp"

class ExprParser {

     public:

        static std::vector<EvaluableToken_ptr> parse
            (const std::vector<AbstractToken_ptr>& tokens);

};

#endif // EXPRPARSER_H

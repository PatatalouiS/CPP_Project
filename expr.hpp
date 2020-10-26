#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <vector>
#include "evaluabletoken.hpp"

class Expr {

    private :

        std::string _exprValue;

        std::vector<EvaluableToken*> _polishedTokens;

    public:

        Expr(const std::string& str);

        double eval() const;

        void print();
};

#endif // EXPR_H

#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <vector>
#include "typealiases.hpp"

class Expr {

    private :

        std::string _exprValue;

        std::vector<EvaluableToken_ptr> _polishedTokens;

    public:

        Expr(const std::string& str);

        double eval() const;

        void print();
};

#endif // EXPR_H

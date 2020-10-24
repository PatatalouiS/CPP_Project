#ifndef EXPR_H
#define EXPR_H

#include <string>
#include "token.hpp"

class Expr {

    private :

        std::string _exprValue;

        std::vector<Token*> _polishedTokens;

    public:

        Expr(const std::string& str);

        double eval() const;

        void print();
};

#endif // EXPR_H

#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <vector>
#include "typealiases.hpp"

class Expr {

    private :

        std::string _exprValue;

        TokenArray _polishedTokens;

        bool setVariable;

        static ValueExpr eval(const TokenArray& tokens, bool setVariable);

    public:

        Expr(const std::string& str);

        ValueExpr eval() const;

        void print();
};

#endif // EXPR_H

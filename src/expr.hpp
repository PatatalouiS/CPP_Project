#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <vector>
#include "typealiases.hpp"



class Expr {

    private :

        std::string _exprValue;

        TokenArray _polishedTokens;

        static double eval(const TokenArray& tokens);

    public:

        Expr(const std::string& str);

        double eval() const;

        void print();
};

#endif // EXPR_H

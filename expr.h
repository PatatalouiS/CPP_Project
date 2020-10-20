#ifndef EXPR_H
#define EXPR_H

#include <string>

class Expr {

    private :

        std::string expr;

    public:

        Expr(const std::string& str);

        double eval() const;

        void print();
};

#endif // EXPR_H

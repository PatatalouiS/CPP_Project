#ifndef EXPRTOKEN_H
#define EXPRTOKEN_H

#include <string>
#include <iostream>

/**
 * @brief The Token class, Abstract and cannot be instancied
 */
class Token {

    public :

        virtual double eval (const double& opA = 0, const double& opB = 0) const = 0;

        virtual bool isOperator () const = 0;

        virtual void print(std::ostream& out) const = 0;

        inline friend std::ostream& operator<< (std::ostream& out, const Token& t) {
            t.print(std::cout);
            return out;
        }

        virtual ~Token() = default;
};

#endif // EXPRTOKEN_H


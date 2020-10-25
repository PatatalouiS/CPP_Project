#ifndef EVALUABLETOKEN_H
#define EVALUABLETOKEN_H

#include <string>
#include <iostream>

#include "abstracttoken.hpp"

/**
 * @brief The Token class, Abstract and cannot be instancied
 */
class EvaluableToken : public AbstractToken {

    public :

        virtual double eval (const double& opA = 0, const double& opB = 0) const = 0;

        virtual bool isOperator () const = 0;

        virtual bool isValue() const = 0;

        virtual void print(std::ostream& out) const = 0;

        virtual ~EvaluableToken() = default;
};

#endif // EXPRTOKEN_H


#ifndef UNARYOP_HPP
#define UNARYOP_HPP

#include "operator.hpp"

class UnaryOp : public Operator {

    public:

        using Operator::Operator;

        double eval(const double& op, const double&) const override final;

        unsigned int precedence() const override final;

        inline bool isUnary() const override final { return true; }

        inline void print(std::ostream & out) const override final {
            out << "UnaryOp(" << _symbol << ")";
        }
};

#endif // UNARYOP_HPP

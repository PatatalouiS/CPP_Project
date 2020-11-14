#ifndef UNARYOP_HPP
#define UNARYOP_HPP

#include "operator.hpp"

class UnaryOp : public Operator {

    public:

        UnaryOp(const char symbol) :
            Operator(symbol, symbol == '+' ? Type::U_ADD : Type::U_MIN) {}

        double eval(std::stack<AbstractToken_ptr>& stack) const override final;

        unsigned int precedence() const override final;

        inline bool isUnary() const override final { return true; }

        inline void print(std::ostream & out) const override final {
            out << "UnaryOp(" << _symbol << ")";
        }
};

#endif // UNARYOP_HPP

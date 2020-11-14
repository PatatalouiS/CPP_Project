#ifndef BINARYOP_H
#define BINARYOP_H

#include "operator.hpp"

class BinaryOp : public Operator {

    public:

        BinaryOp(const char symbol) :
            Operator(symbol, static_cast<Type>(symbol))
        {}

        double eval(std::stack<AbstractToken_ptr>&) const override final;

        unsigned int precedence() const override final;

        inline bool isUnary() const override final { return false; }

        inline void print(std::ostream &out) const override final {
            out << "BinaryOp(" << _symbol << ")";
        }
};

#endif // BINARYOP_H

#ifndef BINARYOP_H
#define BINARYOP_H

#include "operator.hpp"

class BinaryOp : public Operator {

    public:

        BinaryOp() = delete;

        using Operator::Operator;

        ValueExpr eval(std::stack<AbstractToken_ptr>&) const override final;

        unsigned int precedence() const override final;

        inline bool isBinary() const override { return true; }

        inline void print(std::ostream &out) const override final {
            out << "BinaryOp(" << _symbol << ")";
        }
};

#endif // BINARYOP_H

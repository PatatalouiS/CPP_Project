#ifndef BINARYOP_H
#define BINARYOP_H

#include "operator.hpp"
#include "constants.hpp"

class BinaryOp : public Operator {

    public:

        BinaryOp(const char symbol) : Operator(symbol, TokenType::BINARY_OP) {}

        double eval(const double& opA, const double& opB) const override;

        unsigned int precedence() const override final;

        inline bool isUnary() const override final { return false; }

        inline void print(std::ostream &out) const override final {
            out << "BinaryOp(" << _symbol << ")";
        }
};

#endif // BINARYOP_H

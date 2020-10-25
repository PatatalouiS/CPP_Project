#ifndef BINARYOP_H
#define BINARYOP_H

#include "evaluabletoken.hpp"

using BinaryOperation = std::function<double(const double&, const double&)>;

class BinaryOp : public EvaluableToken {
    public:

        inline BinaryOp(const char symbol) : _symbol(symbol) {};

        double eval(const double& opA, const double& opB) const override;

        inline bool isOperator() const override { return true; };

        inline bool isValue() const override { return false; };

        inline void print(std::ostream &out) const override final {
            out << "BinaryOp(" << _symbol << ")";
        }

        bool operator>= (const BinaryOp& other) const;

    private :

        char _symbol;
};

#endif // BINARYOP_H

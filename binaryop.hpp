#ifndef BINARYOP_H
#define BINARYOP_H

#include "token.hpp"

using BinaryOperation = std::function<double(const double&, const double&)>;

class BinaryOp : public Token {
    public:

        inline BinaryOp(const char symbol) : _symbol(symbol) {};

        double eval(const double& opA, const double& opB) const override;

        inline bool isOperator() const override { return true; };

        void print(std::ostream &out) const override final {
            out << "BinaryOp(" << _symbol << ")";
        }

        bool operator>= (const BinaryOp& other) const;

    private :

        char _symbol;
};

#endif // BINARYOP_H

#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "abstracttoken.hpp"

class Operator : public AbstractToken {

    public:

        inline Operator(const char symbol) :
            AbstractToken(Type::OPERATOR),
            _symbol(symbol)
        {};

        inline std::string str() const override final { return std::string(1, _symbol); }

        inline bool isOperator() const override { return true; }

        inline virtual bool isSet() const { return false; }

        inline virtual bool isUnary() const { return false; }

        inline virtual bool isBinary() const { return false; }

        virtual ValueExpr eval(std::stack<AbstractToken_ptr>&) const override = 0;

        virtual unsigned int precedence() const = 0;

        virtual inline void print(std::ostream &out) const override = 0;

        bool operator>= (const Operator& other) const;

    protected:

        char _symbol;
};

#endif // OPERATOR_HPP

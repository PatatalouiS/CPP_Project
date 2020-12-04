#ifndef SETOPERATOR_HPP
#define SETOPERATOR_HPP

#include "operator.hpp"
#include "constants.hpp"

class SetOperator : public Operator {
    public :

        inline SetOperator() : Operator(Operators::SET) {};

        virtual ValueExpr eval(std::stack<AbstractToken_ptr> &) const override;

        inline virtual unsigned int precedence() const override { return 1; };

        inline bool isSet() const override { return true; }

        virtual inline void print(std::ostream &out) const override;

    private :

        static ValueExpr setNewVar(std::stack<AbstractToken_ptr>& stack);

        static ValueExpr setNewFunction(std::stack<AbstractToken_ptr>& stack);
};

#endif // SETOPERATOR_HPP

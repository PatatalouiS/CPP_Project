#ifndef VALUE_HPP
#define VALUE_HPP

#include "evaluabletoken.hpp"

class Value : public EvaluableToken {

    public:

        virtual double eval (const double& opA = 0, const double& opB = 0) const override = 0;

    virtual bool isOperator () const override final { return false; }

    virtual bool isValue() const override final { return true; }

    virtual bool isID() const override = 0;

    virtual void print(std::ostream& out) const override = 0;

    virtual std::string str() const override = 0;

    virtual ~Value() = default;
};

#endif // VALUE_HPP

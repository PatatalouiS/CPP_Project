#ifndef VALUE_H
#define VALUE_H

#include "evaluabletoken.hpp"
#include <string>

class Value : public EvaluableToken {

    public:
        Value() = delete;

        inline Value(const double& value) : EvaluableToken(TokenType::CONST), _value(value) {};

        inline double eval(const double&, const double&) const override final {
            return _value;
        };

        inline bool isOperator() const override final { return false; }

        inline bool isValue() const override final { return true; }

        inline bool isID() const override final { return false; }

        inline std::string str() const override final { return std::to_string(_value); }

        inline void print(std::ostream &out) const override final {
            out << "Value(" << _value << ")";
        };

    private:

        double _value;
};

#endif // VALUE_H

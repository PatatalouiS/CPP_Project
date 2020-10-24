#ifndef VALUE_H
#define VALUE_H

#include "token.hpp"
#include <string>

class Value : public Token {

    public:

        Value() = delete;

        inline Value(const double& value) : _value(value) {};

        inline double eval(const double& a = 0, const double& b = 0) const override final {
            (void) a; (void) b; return _value;
        };

        inline bool isOperator() const override final { return false; };

        inline void print(std::ostream &out) const override final {
            out << "Value(" << _value << ")";
        };

    private:

        double _value;
};

#endif // VALUE_H

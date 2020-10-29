#ifndef VALUE_H
#define VALUE_H

#include "value.hpp"
#include <string>

class Const : public Value {

    public:
        Const() = delete;

        inline Const(const double& value) : _value(value) {};

        inline double eval(const double&, const double&) const override final {
            return _value;
        };

        inline bool isID() const override final { return false; }

        inline std::string str() const override final { return std::to_string(_value); }

        inline void print(std::ostream &out) const override final {
            out << "Value(" << _value << ")";
        };

    private:

        double _value;
};

#endif // VALUE_H

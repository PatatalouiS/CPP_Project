#ifndef VALUE_H
#define VALUE_H

#include "abstracttoken.hpp"
#include <string>

class Const : public AbstractToken {

    public:
        Const() = delete;

        inline Const(const double& value) :
            AbstractToken(Type::CONST),
            _value(value) {};

        inline ValueExpr eval(std::stack<AbstractToken_ptr>&) const override final {
            return _value;
        };

        inline bool isConst() const override final { return true; }

        inline std::string str() const override final { return std::to_string(_value); }

        inline void print(std::ostream &out) const override final {
            out << "Value(" << _value << ")";
        };

    private:

        double _value;
};

#endif // VALUE_H

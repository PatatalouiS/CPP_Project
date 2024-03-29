#ifndef ABSTRACTTOKEN_HPP
#define ABSTRACTTOKEN_HPP

#include <iostream>
#include <stack>
#include <memory>
#include <optional>
#include <variant>

#include "funcutils.hpp"

enum class Type {
    LPAR,
    RPAR,
    COMMA,
    SEMI,
    OPERATOR,
    ID,
    CONST,
    FUNC,
    PLACEHOLDER
};


using ValueExpr = std::variant<double, FuncResult>;

class AbstractToken {

    public:

        using AbstractToken_ptr = std::shared_ptr<AbstractToken>;

        inline AbstractToken(Type type) : _type(type) {}

        virtual bool isOperator () const { return false; }

        virtual bool isConst() const { return false; }

        virtual bool isID() const { return false; }

        virtual bool isFunc() const { return false; }

        virtual bool isPlaceHolder() const { return false; }

        virtual std::string str() const = 0;

        virtual void print(std::ostream& out) const = 0;

        virtual ValueExpr eval(std::stack<AbstractToken_ptr>& stack) const = 0;

        inline friend std::ostream& operator<< (std::ostream& out, const AbstractToken& t) {
            t.print(std::cout);
            return out;
        }

        virtual ~AbstractToken() = default;

        inline Type type() const { return _type; }

    protected :

        Type _type;
};

#endif // ABSTRACTTOKEN_HPP

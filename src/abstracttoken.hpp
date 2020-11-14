#ifndef ABSTRACTTOKEN_HPP
#define ABSTRACTTOKEN_HPP

#include <iostream>
#include <stack>

enum class Type : char {
    LPAR  = '(',
    RPAR  = ')',
    COMMA = ',',
    ADD   = '+',
    MIN   = '-',
    DIV   = '/',
    MUL   = '*',
    SET   = '=',
    U_ADD = 'p',
    U_MIN = 'm',
    ID,
    CONST,
    FUNC
};

class AbstractToken {

    public:

        using AbstractToken_ptr = std::shared_ptr<AbstractToken>;

        inline AbstractToken(Type type) : _type(type) {};

        virtual bool isOperator () const = 0;

        virtual bool isValue() const = 0;

        virtual bool isID() const = 0;

        virtual bool isFunc() const = 0;

        virtual std::string str() const = 0;

        virtual void print(std::ostream& out) const = 0;

        virtual double eval(std::stack<AbstractToken_ptr>& stack) const = 0;

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

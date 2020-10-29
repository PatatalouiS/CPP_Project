#ifndef ABSTRACTTOKEN_HPP
#define ABSTRACTTOKEN_HPP

#include <iostream>
#include "constants.hpp"

class AbstractToken {
    public:

        AbstractToken(TokenType type) : _type(type) {};

        virtual void print(std::ostream& out) const = 0;

        virtual bool isOperator () const = 0;

        virtual bool isValue() const = 0;

        virtual bool isID() const = 0;

        virtual std::string str() const = 0;

        inline TokenType type() { return _type; }

        inline friend std::ostream& operator<< (std::ostream& out, const AbstractToken& t) {
            t.print(std::cout);
            return out;
        }

        virtual ~AbstractToken() = default;

        protected:

        TokenType _type;
};

#endif // ABSTRACTTOKEN_HPP

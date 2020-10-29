#ifndef ABSTRACTTOKEN_HPP
#define ABSTRACTTOKEN_HPP

#include <iostream>

class AbstractToken {

    public:

        virtual bool isOperator () const = 0;

        virtual bool isValue() const = 0;

        virtual bool isID() const = 0;

        virtual std::string str() const = 0;

        virtual void print(std::ostream& out) const = 0;

        inline friend std::ostream& operator<< (std::ostream& out, const AbstractToken& t) {
            t.print(std::cout);
            return out;
        }

        virtual ~AbstractToken() = default;
};

#endif // ABSTRACTTOKEN_HPP

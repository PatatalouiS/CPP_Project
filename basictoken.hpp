#ifndef BASICTOKEN_HPP
#define BASICTOKEN_HPP

#include "abstracttoken.hpp"

enum class U_Token {
    LPAR,
    RPAR
};

class BasicToken : public AbstractToken {

    public:

        inline BasicToken(const U_Token token) : _token(token) {}

        virtual inline void print(std::ostream &out) const override = 0;

        inline bool isOperator() const override final { return false; }

        inline bool isValue() const override final { return  false; }

        U_Token get() const {
            return _token;
        }

    protected:

        U_Token _token;
};

#endif // UNSEMANTICTOKEN_HPP

#ifndef LAPR_H
#define LAPR_H

class LPAR : public BasicToken {
    public :
        LPAR() : BasicToken(U_Token::LPAR) {}
        inline void print(std::ostream& out) const override final {
            out << "LPAR";
        }
};

#endif // LAPR_H

#ifndef RPAR_H
#define RPAR_H

class RPAR : public BasicToken {
    public :
        RPAR() : BasicToken(U_Token::RPAR) {}
        inline void print(std::ostream& out) const override final {
            out << "RPAR";
        }
};

#endif// RPAR_H

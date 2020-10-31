#ifndef BASICTOKEN_HPP
#define BASICTOKEN_HPP

#include "abstracttoken.hpp"
#include "constants.hpp"

class BasicToken : public AbstractToken {

    public:

        inline BasicToken(const std::string& token) : _token(token) {};

        virtual inline void print(std::ostream &out) const override = 0;

        inline bool isOperator() const override final { return false; }

        inline bool isValue() const override final { return false; }

        inline bool isID() const override final { return false; }

        inline std::string str() const override final { return _token; }

        virtual ~BasicToken() = default;

    protected:

        std::string _token;
};

#endif // UNSEMANTICTOKEN_HPP

#ifndef LAPR_H
#define LAPR_H

class LPAR : public BasicToken {
    public :
        LPAR() : BasicToken(BasicCharacters::LPAR) {}
        inline void print(std::ostream& out) const override final {
            out << "LPAR";
        }
};

#endif // LAPR_H

#ifndef RPAR_H
#define RPAR_H

class RPAR : public BasicToken {
    public :
        RPAR() : BasicToken(BasicCharacters::RPAR) {}
        inline void print(std::ostream& out) const override final {
            out << "RPAR";
        }
};

#endif// RPAR_H

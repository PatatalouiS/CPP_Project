#ifndef BASICTOKEN_HPP
#define BASICTOKEN_HPP

#include "abstracttoken.hpp"
#include "constants.hpp"

class BasicToken : public AbstractToken {

    public:

        inline BasicToken(const std::string& token) : _token(token) {};

        inline bool isOperator() const override final { return false; }

        inline bool isValue() const override final { return false; }

        inline bool isID() const override final { return false; }

        inline std::string str() const override final { return _token; }

        inline void print(std::ostream& out) const override final { out << _token; }

        virtual ~BasicToken() = default;

    protected:

        std::string _token;
};

#endif // UNSEMANTICTOKEN_HPP

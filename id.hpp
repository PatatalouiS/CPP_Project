#ifndef ID_HPP
#define ID_HPP

#include "evaluabletoken.hpp"
#include "constants.hpp"
#include <optional>

class ID : public EvaluableToken {

    public:

        inline ID(const std::string& id) : EvaluableToken(TokenType::ID), _id(id) {}

        double eval(const double&, const double&) const override final;

        inline bool isOperator() const override final { return false; }

        inline bool isValue() const override final { return true; }

        inline bool isID() const override final { return true; }

        inline void set(double& value) { _value = value; }

        virtual void print(std::ostream& out) const override final;

        inline std::string str() const override final { return _id; }

    private:

        std::string _id;
        std::optional<double> _value;
};

#endif // ID_HPP

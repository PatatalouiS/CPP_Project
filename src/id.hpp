#ifndef ID_HPP
#define ID_HPP

#include "abstracttoken.hpp"
#include <optional>

class ID : public AbstractToken {

    public:

        ID() = delete;

        inline ID(const std::string& id) :
            AbstractToken(Type::ID),
            _id(id)
        {}

        double eval(std::stack<AbstractToken_ptr>& eval) const override final;

        inline bool isID() const override final { return true; }

        inline bool isOperator() const override final { return false; }

        inline bool isConst() const override final { return false; }

        inline bool isFunc() const override final { return false; }

        inline void set(double& value) { _value = value; }

        virtual void print(std::ostream& out) const override final;

        inline std::string str() const override final { return _id; }

    private:

        std::string _id;
        std::optional<double> _value;
};

#endif // ID_HPP

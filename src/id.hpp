#ifndef ID_HPP
#define ID_HPP

#include "value.hpp"
#include <optional>

class ID : public Value {

    public:

        inline ID(const std::string& id) : _id(id) {}

        double eval(const double&, const double&) const override final;

        inline bool isID() const override final { return true; }

        inline void set(double& value) { _value = value; }

        virtual void print(std::ostream& out) const override final;

        inline std::string str() const override final { return _id; }

    private:

        std::string _id;
        std::optional<double> _value;
};

#endif // ID_HPP

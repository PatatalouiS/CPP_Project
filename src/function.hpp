#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include "abstracttoken.hpp"
#include "typealiases.hpp"

using Args = std::vector<double>;
using ComputeHandler = std::function<double(const Args&)>;

struct FunctionDescriptor {
    unsigned int nbArgs;
    bool variadic;
    ComputeHandler fct;
};

using FunctionMapper = std::unordered_map<std::string, FunctionDescriptor>;

class Func : public AbstractToken {

    public:

        Func(const std::string& name);

        inline bool isOperator() const override final { return false; }

        inline bool isValue() const override final { return false; }

        inline bool isID() const override final { return false; }

        inline bool isFunc() const override final { return true; }

        inline std::string str() const override final { return _name ;}

        double eval(std::stack<AbstractToken_ptr>& stack) const override final;

        void print(std::ostream& out) const override final;

        inline void setNbArgs(const unsigned int nbArgs) { _nbArgs = nbArgs; }

        bool isVariadic() const;

    private:

        std::string _name;

        unsigned int _nbArgs;

        static const FunctionMapper mapper;
};

#endif // FUNCTION_HPP

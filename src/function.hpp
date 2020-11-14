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
    ComputeHandler fct;
};

using FunctionMapper = std::unordered_map<std::string, FunctionDescriptor>;

class Func : public AbstractToken {

    public:


        Func(const std::string& name);

        inline bool isOperator() const override final { return false; }

        inline bool isValue() const override final { return false; }

        inline bool isID() const override final { return false; }

        inline std::string str() const override final { return _name ;}

        static bool isFunction(const std::string& str);

        static unsigned int nbArgs(const std::string& funcName);

        static double eval(const std::string& name, const std::vector<double>& args);

        void print(std::ostream& out) const override final;

    private:

        std::string _name;

        static const FunctionMapper mapper;
};

#endif // FUNCTION_HPP

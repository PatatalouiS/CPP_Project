#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "abstracttoken.hpp"
#include "typealiases.hpp"

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

using Args = std::vector<double>;

class Func : public AbstractToken {

    public:

        using ComputeHandler = std::function<double(const Args&)>;

        struct FunctionDescriptor {
            unsigned int nbArgs;
            bool variadic;
            ComputeHandler fct;
        };

        using FunctionMapper = std::unordered_map<std::string, FunctionDescriptor>;


        Func() = delete;

        Func(const std::string& name, const std::optional<unsigned int> nbArgs);

        inline bool isOperator() const override final { return false; }

        inline bool isConst() const override final { return false; }

        inline bool isID() const override final { return false; }

        inline bool isFunc() const override final { return true; }

        inline std::string str() const override final { return _name ;}

        double eval(std::stack<AbstractToken_ptr>& stack) const override final;

        void print(std::ostream& out) const override final;

        inline void setNbArgs(const unsigned int nbArgs) { _nbArgs = nbArgs; }

        const std::optional<unsigned int>& nbArgs() const;

        bool isVariadic() const;

        static bool isDefined(const Func& func);

    private:

        std::string _name;

        std::optional<unsigned int> _nbArgs;

        static const FunctionMapper mapper;
};

#endif // FUNCTION_HPP

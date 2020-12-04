#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "abstracttoken.hpp"
#include "typealiases.hpp"
#include "funcutils.hpp"

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

class Func : public AbstractToken {

    public:

        Func() = delete;

        Func(const std::string& name, const std::optional<unsigned int> nbArgs);

        inline bool isFunc() const override final { return true; }

        inline std::string str() const override final { return _name ;}

        ValueExpr eval(std::stack<AbstractToken_ptr>& stack) const override final;

        void print(std::ostream& out) const override final;

        inline void setNbArgs(const unsigned int nbArgs) { _nbArgs = nbArgs; }

        const std::optional<unsigned int>& nbArgs() const;

        bool isVariadic() const;

        static bool isDefined(const Func& func);

        static bool isValidForCurrying(const Func& func);

        static void putFunction(const std::string& name, const FunctionDescriptor& func);

        const FunctionDescriptor& getDescriptor();

        bool isIncomplete() const;

        void setPlaceHolder(bool isPlaceHolder);

        inline bool placeHolder() const { return containsPlaceHolder; }

    private:

        std::string _name;

        std::optional<unsigned int> _nbArgs;

        static FunctionMapper mapper;

        bool containsPlaceHolder;
};

#endif // FUNCTION_HPP

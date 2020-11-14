
#include "function.hpp"
#include <variant>
#include <iostream>
#include <cmath>
#include "utils.hpp"

using namespace std;

namespace {

    double lerp(const double& x, const double& a, const double& b) {
        return a + x * (b - a);
    }

    double polynome (const Args& args) {
        auto degree = args.front();
        auto xValue = args.back();
        auto result = 0;

        for(unsigned int i = 0; i <= degree; ++i) {
            result += args[i + 1] * pow(xValue, i);
        }

        return result;
    }

}

const FunctionMapper Func::mapper {{
        { "cos",  { 1, false, [](const Args& args) { return cos(args[0]);                    }}},
        { "sin",  { 1, false, [](const Args& args) { return sin(args[0]);                    }}},
        { "tan",  { 1, false, [](const Args& args) { return tan(args[0]);                    }}},
        { "log",  { 1, false, [](const Args& args) { return log2(args[0]);                   }}},
        { "exp",  { 1, false, [](const Args& args) { return exp(args[0]);                    }}},
        { "sqrt", { 1, false, [](const Args& args) { return sqrt(args[0]);                   }}},
        { "pow",  { 2, false, [](const Args& args) { return pow(args[0], args[1]);           }}},
        { "hypot",{ 2, false, [](const Args& args) { return hypot(args[0], args[1]);         }}},
        { "lerp", { 3, false, [](const Args& args) { return lerp(args[0], args[1], args[2]); }}},

        { "polynome", { INT_MAX, true, [](const Args& args) { return polynome(args);         }}}
}};


Func::Func(const string& name) :
    AbstractToken(Type::FUNC),
    _name(name)
{
    _nbArgs = (mapper.at(_name).nbArgs);
}


void Func::print(ostream& out) const {
    out << "FUN(" << _name << ")";
}

double Func::eval(std::stack<AbstractToken_ptr>& stack) const {
    auto func = mapper.find(_name);

    if(func == mapper.end()) {
        throw EvalError("Error : \"" + _name + "\" is not a function");
    }

    vector<double> args;

    for(unsigned int i = 0; i < _nbArgs; ++i) {
        args.push_back(topAndPop(stack)->eval(stack));
    }

    reverse(args.begin(), args.end());

    return func->second.fct(args);
}

bool Func::isVariadic() const {
    return mapper.at(_name).variadic;
}

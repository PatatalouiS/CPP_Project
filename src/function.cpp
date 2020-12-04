
#include "function.hpp"
#include "utils.hpp"

#include <variant>
#include <iostream>
#include <cmath>
#include <climits>
#include <optional>

using namespace std;

namespace {

    double lerp(const double& x, const double& a, const double& b) {
        return a + x * (b - a);
    }

    double polynome (const Args& args) {
        auto degree = args.front();
        auto xValue = args.back();
        auto result = 0;

        for(unsigned int i = 0; i <= degree; ++i)
            result += args[i + 1] * pow(xValue, i);

        return result;
    }
}

FunctionMapper Func::mapper {{
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


Func::Func(const string& name, const optional<unsigned int> nbArgs) : 
    AbstractToken(Type::FUNC),
    _name(name),
    _nbArgs(nbArgs),
    containsPlaceHolder(false)
{}


void Func::print(ostream& out) const {
    out << "FUN(" << _name << ")";
}

ValueExpr Func::eval(stack<AbstractToken_ptr>& stack) const {
    auto func = mapper.find(_name);

    if(func == mapper.end())
        throw EvalError("Error : \"" + _name + "\" is not a function");

    vector<double> args;

    for(unsigned int i = 0; i < *_nbArgs; ++i)
        args.push_back(get<double>((topAndPop(stack)->eval(stack))));

    reverse(args.begin(), args.end());

    return func->second.fct(args);
}

bool Func::isVariadic() const {
    return mapper.at(_name).variadic;
}

const optional<unsigned int>& Func::nbArgs() const {
    return _nbArgs;
}

bool Func::isDefined(const Func& func) {
    auto find = mapper.find(func.str());
    return (find != mapper.end()) &&
            ((!func.nbArgs()) ||
             (func.nbArgs().value() == find->second.nbArgs) ||
             (func.isVariadic()));
}

bool Func::isValidForCurrying(const Func &func) {
    auto find = mapper.find(func.str());
    return (find != mapper.end()) &&
           (((func.nbArgs().value() < find->second.nbArgs) &&
               (func.nbArgs().value() != 0)) ||
             (func.isVariadic()));
}

const FunctionDescriptor& Func::getDescriptor() {
    return mapper.at(_name);
}

void Func::putFunction(const std::string &name, const FunctionDescriptor &func) {
    auto find = mapper.find(name);

    if(find != mapper.end())
        find->second = func;
    else
        mapper.insert({ name, func });
}

void Func::setPlaceHolder(bool isPlaceholder) {
    containsPlaceHolder = isPlaceholder;
}

bool Func::isIncomplete() const {
    return _nbArgs < mapper.at(_name).nbArgs;
}


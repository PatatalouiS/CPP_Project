
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

    double polynome (const Args&) {
        return 0;
    }
}

const FunctionMapper Func::mapper {{
        { "cos",  { 1, [](const Args& args) { return cos(args[0]);                    }}},
        { "sin",  { 1, [](const Args& args) { return sin(args[0]);                    }}},
        { "tan",  { 1, [](const Args& args) { return tan(args[0]);                    }}},
        { "log",  { 1, [](const Args& args) { return log2(args[0]);                   }}},
        { "exp",  { 1, [](const Args& args) { return exp(args[0]);                    }}},
        { "sqrt", { 1, [](const Args& args) { return sqrt(args[0]);                   }}},
        { "pow",  { 2, [](const Args& args) { return pow(args[0], args[1]);           }}},
        { "hypot",{ 2, [](const Args& args) { return hypot(args[0], args[1]);         }}},
        { "lerp", { 3, [](const Args& args) { return lerp(args[0], args[1], args[2]); }}},

        { "polynome", { INT_MAX, [](const Args& args) { return polynome(args);        }}}
}};


Func::Func(const string& name) :
    AbstractToken(),
    _name(name)
{}

void Func::print(ostream& out) const {
    out << "FUN(" << _name << ")";
}

double Func::eval(const string& name, const std::vector<double>& args) {
    return mapper.at(name).fct(args);
}

bool Func::isFunction(const std::string &str) {
    return mapper.find(str) != mapper.end();
}

unsigned int Func::nbArgs(const std::string &funcName) {
    return mapper.at(funcName).nbArgs;
}

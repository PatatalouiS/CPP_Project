
#include <functional>
#include <unordered_map>
#include "unaryop.hpp"
#include "constants.hpp"
#include "typealiases.hpp"
#include "utils.hpp"

using namespace std;
using namespace Operators;
using UnaryOperation = std::function<double(const double&)>;
using FunctorsMapper = unordered_map<char, UnaryOperation>;

namespace {

const FunctorsMapper mapper {
    { ADD, [](const double& op) { return +op; }},
    { MIN, [](const double& op) { return -op; }}
};

}

double UnaryOp::eval(TokenStack& stack) const {
    return mapper.at(_symbol)(topAndPop(stack)->eval(stack));
}

unsigned int UnaryOp::precedence() const {
    return 4;
}

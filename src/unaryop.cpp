
#include <unordered_map>
#include "unaryop.hpp"
#include "constants.hpp"

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

double UnaryOp::eval(const double &op, const double &) const {
    return mapper.at(_symbol)(op);
}

unsigned int UnaryOp::precedence() const {
    return 4;
}

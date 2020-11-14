#include <unordered_map>
#include <functional>
#include "binaryop.hpp"
#include "constants.hpp"
#include "typealiases.hpp"
#include "utils.hpp"
#include "exprapp.hpp"

using namespace std;
using BinaryOperation = std::function<double(const double&, const double&)>;
using FunctorsMapper = unordered_map<char, BinaryOperation>;
using namespace Operators;


namespace {

const FunctorsMapper mapper {
        { ADD, [](const double& a, const double& b) { return a + b;  }},
        { MIN, [](const double& a, const double& b) { return a - b;  }},
        { MUL, [](const double& a, const double& b) { return a * b;  }},
        { DIV, [](const double& a, const double& b) { return a / b;  }},
};

}

double BinaryOp::eval(TokenStack& stack) const {
    auto b = topAndPop(stack)->eval(stack);
    auto a = topAndPop(stack);

    if(a->isID() && (_symbol == SET)) {
        ExprApp::putVariable({ a->str(), b });
        return b;
    }

    return mapper.at(_symbol)(a->eval(stack), b);
}

unsigned int BinaryOp::precedence() const {
    switch(_symbol) {
        case ADD : return 2; break;
        case MIN : return 2; break;
        case MUL : return 3; break;
        case DIV : return 3; break;
        case SET : return 1; break;
        default :  return -1;
    }
}

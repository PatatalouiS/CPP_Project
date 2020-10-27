#include <unordered_map>

#include "binaryop.hpp"
#include "constants.hpp"

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
        { SET, [](const double& a, const double&  ) { return a;      }}
};

}

double BinaryOp::eval(const double& a, const double& b) const {
    return mapper.at(_symbol)(a, b);
}

unsigned int BinaryOp::precedence() const {
    switch(_symbol) {
        case '+' : return 2; break;
        case '-' : return 2; break;
        case '*' : return 3; break;
        case '/' : return 3; break;
        case '=' : return 1; break;
        default :  return -1;
    }
}

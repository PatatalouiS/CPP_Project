#include "binaryop.hpp"
#include <unordered_map>

using namespace std;
using FunctorsMapper = unordered_map<char, BinaryOperation>;

constexpr char ADD = '+';
constexpr char MIN = '-';
constexpr char DIV = '/';
constexpr char MUL = '*';

namespace {

const FunctorsMapper mapper {
        { ADD, [](const double& a, const double& b) { return a + b; }},
        { MIN, [](const double& a, const  double& b) { return a - b; }},
        { MUL, [](const double& a, const double& b) { return a * b; }},
        { DIV, [](const double& a, const double& b) { return a / b; }},
};

}

double BinaryOp::eval(const double& a, const double& b) const {
    return mapper.at(_symbol)(a, b);
}

bool BinaryOp::operator>=(const BinaryOp& other) const {
        return !(((_symbol == '-') || (_symbol == '+')) &&
                   ((other._symbol == '/') || (other._symbol == '*')));

}

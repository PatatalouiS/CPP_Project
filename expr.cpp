
#include "expr.h"
#include "exprtoken.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>


using StringVector = std::vector<std::string>;
using BinaryOperation = std::function<double(const double&, const double&)>;
using Operations = std::unordered_map<std::string, BinaryOperation>;


const Operations OPERATIONS {
    { PLUS, [](const double& a, const double& b) -> double { return a + b; }},
    { MINUS, [](const double& a, const double& b) -> double { return a - b; }},
    { MULTIPLY, [](const double& a, const double& b) -> double { return a * b; }},
    { DIVIDE, [](const double& a, const double& b) -> double { return a / b; }}
};

constexpr char SPACE{' '};

namespace {

StringVector split(const std::string& s, const char delim = SPACE) {
    StringVector tokenArray;
    std::string token;

    for(auto i : s) {
        if(i != delim) {
            token.push_back(i);
        }
        else {
            tokenArray.emplace_back(std::move(token));
            token.clear();
        }
    }

    tokenArray.emplace_back(std::move(token));
    return tokenArray;
}

std::vector<ExprToken> reverse_polish_notation(const StringVector& tArray) {
    std::stack<ExprToken> stack;
    std::vector<ExprToken> out;

    for(const auto& token : tArray) {
        ExprToken exprToken{ token };
        // It's a litteral
        if(!exprToken.isOperator()) {
            out.push_back(exprToken);
        }// It's an operator
        else {

            while(!stack.empty() && stack.top().isPriority(exprToken)){
                out.push_back(stack.top());
                stack.pop();
            }

            stack.push(exprToken);
        }
    }

    while(!stack.empty()) {
        out.push_back(stack.top());
        stack.pop();
    }

    return out;
}

}

Expr::Expr(const std::string& str) : expr(str) {
}

double Expr::eval() const {
    auto polishArray{reverse_polish_notation(split(expr))};
    std::stack<ExprToken> stack;

    for(const auto& token : polishArray) {
        if(!token.isOperator()) {
            stack.push(token);
        }
        else {
            auto op2{std::stod(stack.top().getStr())};
            stack.pop();
            auto op1{std::stod(stack.top().getStr())};
            stack.pop();
            auto result{OPERATIONS.at(token.getStr())(op1, op2)};
            stack.push(std::to_string(result));
        }
    }

    return std::stod(stack.top().getStr());
}

void Expr::print() {
    std::cout << "Result : " << eval();
}

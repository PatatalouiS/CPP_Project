


#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

#include "exprlexer.hpp"
#include "expr.hpp"
#include "token.hpp"
#include "exprparser.hpp"
#include <stack>
#include "value.hpp"

using namespace std;

namespace {

template<typename T>
void deleteVector(vector<T*>& v) {

    for(auto& val : v) {
        delete val;
    }
    v.clear();
}


}

Expr::Expr(const std::string& str) :
    _exprValue(str),
    _polishedTokens(ExprParser::parse(ExprLexer::tokenize(str)))
{}

double Expr::eval() const {
    stack<Token*> stack;
    vector<Value> tempResults;

       for(auto& token : _polishedTokens) {
           if(!token->isOperator()) {
               stack.push(token);
           }
           else {
               auto op2(stack.top()->eval());
               stack.pop();
               auto op1(stack.top()->eval());
               stack.pop();
               tempResults.push_back({ token->eval(op1, op2) });
               stack.emplace(&tempResults.back());
           }
       }

       return stack.top()->eval();
}

void Expr::print() {
    for(auto& token : _polishedTokens) {
        cout << *token << endl;
    }
}

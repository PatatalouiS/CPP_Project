
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

#include "exprlexer.hpp"
#include "expr.hpp"
#include "evaluabletoken.hpp"
#include "exprparser.hpp"
#include <stack>
#include "value.hpp"
#include "operator.hpp"
#include "utils.hpp"

using namespace std;
using namespace PrintUtils;

void printStack(stack<EvaluableToken*> s) {
    cout << "PRINT_STACK" << endl;
    while(!s.empty()) {
         cout << *s.top() << " | ";
         s.pop();
    }
    cout << endl;
}

void printVec(const vector<AbstractToken*>& s) {
    cout << endl << "PRINT_VEC" << endl;
    for(auto& i : s) {
        cout << *i << " | ";
    }
    cout << endl << endl;
}

void printVecE(const vector<EvaluableToken*>& s) {
    cout << endl << "PRINT_VEC" << endl;
    for(auto& i : s) {
        cout << *i << " | ";
    }
    cout << endl << endl;
}

template<typename T>
T* topAndPop(stack<T*>& stack) {
    auto ptr = stack.top();
    stack.pop();
    return ptr;
}

Expr::Expr(const std::string& str) {
    auto tokens = ExprLexer::tokenize(str);
    printVec(tokens);
    auto parsedTokens = ExprParser::parse(tokens);
    printVecE(parsedTokens);
    _polishedTokens = parsedTokens;
}

double Expr::eval() const {
    stack<EvaluableToken*> stack;
    vector<unique_ptr<Value>> tempResults;

       for(auto& token : _polishedTokens) {
           //cout << "CurrentToken :  " << *token << endl;;
           if(!token->isOperator()) {
               stack.push(token);
           }
           else {
               auto currentOperator = static_cast<Operator*>(token);
               auto op1 = topAndPop(stack)->eval();

               if(currentOperator->isUnary()) {
                   tempResults.emplace_back(make_unique<Value>(token->eval(op1)));
                   //cout << "ONE_OP :  " << op << endl;
               }
               else {
                   auto op2 = topAndPop(stack)->eval();
                   //cout << "TWO_OP_2 :  " << op2 << endl;
                   tempResults.emplace_back(make_unique<Value>(token->eval(op2, op1)));
               }

               stack.push(tempResults.back().get());
           }
           //cout << "STACK_SIZE : " << stack.size() << endl << endl;
       }
       return stack.top()->eval();
}

void Expr::print() {
    for(auto& token : _polishedTokens) {
        cout << *token << endl;
    }
}

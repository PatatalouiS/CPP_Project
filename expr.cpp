
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
#include "constants.hpp"
#include "id.hpp"
#include "exprapp.hpp"

using namespace std;
using namespace PrintUtils;

template<typename T>
T topAndPop(stack<T>& stack) {
    auto ptr = stack.top();
    stack.pop();
    return ptr;
}

Expr::Expr(const std::string& str) {
    auto tokens = ExprLexer::tokenize(str);
    auto parsedTokens = ExprParser::parse(tokens);
    _polishedTokens = parsedTokens;
}

double Expr::eval() const {
    stack<EvaluableToken_ptr> stack;
    vector<Value_ptr> tempResults;

    //printVector(_polishedTokens);

       for(auto& token : _polishedTokens) {
           //cout << "CurrentToken :  " << *token << endl;;
           if(!token->isOperator()) {
               stack.push(token);
           }
           else {
               auto currentOperator = static_pointer_cast<Operator>(token);
               auto op1 = topAndPop(stack)->eval();

               if(currentOperator->isUnary()) {
                   tempResults.emplace_back(make_unique<Value>(token->eval(op1)));
                   //cout << "ONE_OP :  " << op1 << endl;
               }
               else {
                   if(currentOperator->str()[0] == Operators::SET) {
                       auto op2 = static_pointer_cast<ID>(topAndPop(stack));
                       ExprApp::putVariable({ op2->str(), op1 });
                       tempResults.emplace_back(make_unique<Value>(op1));
                   }
                   else {
                       auto op2 = topAndPop(stack)->eval();
                       //cout << "TWO_OP_2 :  " << op2 << endl;
                       tempResults.emplace_back(make_unique<Value>(token->eval(op2, op1)));
                   }
               }

               stack.push(tempResults.back());
           }
       }

//       for(auto& [key, value] : ExprApp::memory ) {
//           cout << "Key : " << key << "    Value : " << value << endl;
//       }

//       cout << endl;

       return stack.top()->eval();
}

void Expr::print() {
    for(auto& token : _polishedTokens) {
        cout << *token << endl;
    }
}


#include "utils.hpp"
#include "expr.hpp"
#include "exprlexer.hpp"
#include "exprparser.hpp"
#include "id.hpp"
#include "exprapp.hpp"

#include <stack>


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
    vector<Const_ptr> tempResults;

       for(auto& token : _polishedTokens) {
           if(!token->isOperator()) {
               stack.push(token);
           }
           else {
               auto currentOperator = static_pointer_cast<Operator>(token);
               auto op1 = topAndPop(stack)->eval();

               if(currentOperator->isUnary()) {
                   tempResults.emplace_back(make_unique<Const>(token->eval(op1)));
               }
               else {
                   if(currentOperator->str()[0] == Operators::SET) {
                       auto op2 = static_pointer_cast<ID>(topAndPop(stack));
                       ExprApp::putVariable({ op2->str(), op1 });
                       tempResults.emplace_back(make_unique<Const>(op1));
                   }
                   else {
                       auto op2 = topAndPop(stack)->eval();
                       tempResults.emplace_back(make_unique<Const>(token->eval(op2, op1)));
                   }
               }
               stack.push(tempResults.back());
           }
       }
       return stack.top()->eval();
}

void Expr::print() {
    for(auto& token : _polishedTokens) {
        cout << *token << endl;
    }
}


#include "utils.hpp"
#include "expr.hpp"
#include "exprlexer.hpp"
#include "exprparser.hpp"
#include "id.hpp"
#include "exprapp.hpp"
#include "function.hpp"

#include <memory>
#include <algorithm>
#include <stack>

using namespace std;

Expr::Expr(const std::string& str) {
    auto tokens = ExprLexer::tokenize(str);
    _polishedTokens = ExprParser::parse(tokens);
}

double Expr::eval(const TokenArray& tokens)  {
    TokenStack stack;
    Const_ptr result;

    for (const auto& token : tokens) {
        if(token->isID() && (tokens.back()->str().front() == Operators::SET)) {
            stack.push(token);
        }
        else {
            result = make_shared<Const>(token->eval(stack));
            stack.push(result);
        }
    }

    return stack.top()->eval(stack);
}

double Expr::eval() const  {
    return eval(_polishedTokens);
}

void Expr::print() {
    for(auto& token : _polishedTokens)
        cout << *token << endl;
}


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
using namespace PrintUtils;

Expr::Expr(const std::string& str) {
    auto tokens = ExprLexer::tokenize(str);
    auto parsedTokens = ExprParser::parse(tokens);
     _polishedTokens = parsedTokens;
}

double Expr::eval(const TokenArray& tokens)  {
    TokenStack stack;
    Const_ptr result;

    for ( const auto& token : tokens ) {
        if(!token->isID() || ExprApp::isDefined(token->str())) {
            result = make_shared<Const>(token->eval(stack));
            stack.push(result);
        }
        else {
            stack.push(token);
        }
    }

    return stack.top()->eval(stack);
}


double Expr::eval() const  {
    return eval(_polishedTokens);
}

void Expr::print() {
    for(auto& token : _polishedTokens) {
        cout << *token << endl;
    }
}

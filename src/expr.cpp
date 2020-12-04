
#include "utils.hpp"
#include "expr.hpp"
#include "exprlexer.hpp"
#include "exprparser.hpp"
#include "id.hpp"
#include "exprapp.hpp"
#include "function.hpp"
#include <iomanip>
#include <type_traits>

#include <memory>
#include <algorithm>
#include <stack>

using namespace std;

namespace {

bool toDefineLater(const AbstractToken_ptr & t, bool setVariable) {
    return setVariable && ((t->isID()) || (t->isFunc() &&
                           (tokenCast_ptr<Func>(t)->isIncomplete() ||
                           tokenCast_ptr<Func>(t)->placeHolder())));
}

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

}

Expr::Expr(const std::string& str) {
    auto tokens = ExprLexer::tokenize(str);
    _polishedTokens = ExprParser::parse(tokens);
    if(_polishedTokens.back()->str().front() == Operators::SET)
        setVariable = true;
}

ValueExpr Expr::eval(const TokenArray& tokens,  bool setVariable)  {
    TokenStack stack;
    ValueExpr result;

    for (const auto& token : tokens) {

        if(toDefineLater(token, setVariable) || token->isPlaceHolder()) {
            stack.push(token);
        }
        else {
            visit(overloaded {
                [&stack](const double& value) {
                    stack.emplace(make_shared<Const>(value));
                },
                [&stack](const FuncResult& func) {
                   stack.emplace(make_shared<Func>(func.first, func.second.nbArgs));
                }
            }, token->eval(stack));
        }
    }

    if(stack.top()->isFunc()) {
        auto func = *tokenCast_ptr<Func>(stack.top());
        return make_pair(func.str(), func.getDescriptor());
    }

   return get<double>(stack.top()->eval(stack));
}

ValueExpr Expr::eval() const  {
    return eval(_polishedTokens, setVariable);
}

void Expr::print() {
    for(auto& token : _polishedTokens)
        cout << *token << endl;
}

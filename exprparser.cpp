#include "exprparser.hpp"
#include "binaryop.hpp"
#include "typealiases.hpp"
#include "basictoken.hpp"

#include <stack>

using namespace std;

EvaluableToken* toEvaluableToken(AbstractToken* token) {
    return static_cast<EvaluableToken*>(token);
}

void parseBasicToken(BasicToken* uToken,
                       stack<AbstractToken*>& stack,
                       vector<EvaluableToken*>& out ) {
    auto uValue = uToken->get();

    if(uValue == U_Token::LPAR) {
        stack.push(uToken);
    }
    else {
        while(stack.top()->isOperator()) {
            out.push_back(toEvaluableToken(stack.top()));
            stack.pop();
        }
        stack.pop();
    }
}

void parseBinaryOp(BinaryOp* token,
                        stack<AbstractToken*>& stack,
                        vector<EvaluableToken*>& out) {
    while(!stack.empty() &&
          stack.top()->isOperator() &&
        (*static_cast<BinaryOp*>(stack.top()) >= *token)){

        out.push_back(toEvaluableToken(stack.top()));
        stack.pop();
    }

    stack.push(token);
}

vector<EvaluableToken*> ExprParser::parse(const vector<AbstractToken*>& tokens) {
    stack<AbstractToken*> stack;
        vector<EvaluableToken*> out;

        for(auto& token : tokens) {
            if(token->isValue()) {
                out.push_back(toEvaluableToken(token));
            }
            else if(token->isOperator()) {
                parseBinaryOp(static_cast<BinaryOp*>(token), stack, out);
            }
            else parseBasicToken(static_cast<BasicToken*>(token), stack, out);
        }

        while(!stack.empty()) {
            out.push_back(toEvaluableToken(stack.top()));
            stack.pop();
        }

        return out;
}

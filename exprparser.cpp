#include "exprparser.hpp"
#include "binaryop.hpp"
#include "typealiases.hpp"
#include "basictoken.hpp"
#include "constants.hpp"

#include <stack>

using namespace std;

EvaluableToken* toEvaluableToken(AbstractToken* token) {
    return static_cast<EvaluableToken*>(token);
}

void parseBasicToken(BasicToken* uToken,
                       stack<AbstractToken*>& stack,
                       vector<EvaluableToken*>& out ) {
    auto uValue = uToken->str();

    if(uValue == BasicCharacters::LPAR) {
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

void parseOperator(Operator* token,
                        stack<AbstractToken*>& stack,
                        vector<EvaluableToken*>& out) {
    while(!stack.empty() &&
          stack.top()->isOperator() &&
        (*static_cast<Operator*>(stack.top()) >= *token)){

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
                parseOperator(static_cast<Operator*>(token), stack, out);
            }
            else parseBasicToken(static_cast<BasicToken*>(token), stack, out);
        }

        while(!stack.empty()) {
            out.push_back(toEvaluableToken(stack.top()));
            stack.pop();
        }

        return out;
}

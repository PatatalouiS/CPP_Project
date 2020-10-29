#include "exprparser.hpp"
#include "binaryop.hpp"
#include "typealiases.hpp"
#include "basictoken.hpp"
#include "constants.hpp"
#include "exprapp.hpp"

#include <stack>

using namespace std;

template <typename T>
shared_ptr<T> tokenCast_ptr(AbstractToken_ptr token) {
    return static_pointer_cast<T>(token);
}

void parseBasicToken(BasicToken_ptr uToken,
                       stack<AbstractToken_ptr>& stack,
                       vector<EvaluableToken_ptr>& out ) {
    auto uValue = uToken->str();

    if(uValue == BasicCharacters::LPAR) {
        stack.push(uToken);
    }
    else {
        while(stack.top()->isOperator()) {
            out.push_back(tokenCast_ptr<EvaluableToken>(stack.top()));
            stack.pop();
        }
        stack.pop();
    }
}

void parseOperator(Operator_ptr token,
                        stack<AbstractToken_ptr>& stack,
                        vector<EvaluableToken_ptr>& out) {
    while(!stack.empty() &&
          stack.top()->isOperator() &&
        (*tokenCast_ptr<Operator>(stack.top()) >= *token)){

        out.push_back(tokenCast_ptr<EvaluableToken>(stack.top()));
        stack.pop();
    }

    stack.push(token);
}

bool isVariableDefinition(const std::vector<AbstractToken_ptr>& tokens,
                          const AbstractToken_ptr& token) {
    return ((tokens.size() >= 3) && (tokens[0] == token) && (tokens[1]->str() == "="));
}

vector<EvaluableToken_ptr> ExprParser::parse(const vector<AbstractToken_ptr>& tokens) {
    stack<AbstractToken_ptr> stack;
        vector<EvaluableToken_ptr> out;

        for(auto& token : tokens) {
            if(token->isValue()) {
                if(token->isID() && !isVariableDefinition(tokens, token)) {
                    ExprApp::setVariable(tokenCast_ptr<ID>(token));
                }

                out.push_back(tokenCast_ptr<EvaluableToken>(token));
            }
            else if(token->isOperator()) {
                parseOperator(tokenCast_ptr<Operator>(token), stack, out);
            }
            else parseBasicToken(tokenCast_ptr<BasicToken>(token), stack, out);
        }

        while(!stack.empty()) {
            out.push_back(tokenCast_ptr<EvaluableToken>(stack.top()));
            stack.pop();
        }

        return out;
}

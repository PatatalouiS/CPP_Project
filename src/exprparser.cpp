
#include "typealiases.hpp"
#include "exprparser.hpp"
#include "exprapp.hpp"
#include "constants.hpp"
#include "error.hpp"

#include <vector>
#include <stack>

using namespace std;

template <typename T>
shared_ptr<T> tokenCast_ptr(AbstractToken_ptr token) {
    return static_pointer_cast<T>(token);
}

namespace {

void parseBasicToken(BasicToken_ptr uToken,
                       stack<AbstractToken_ptr>& stack,
                       vector<EvaluableToken_ptr>& out ) {
    auto uValue = uToken->str();

    if(uValue == BasicCharacters::LPAR) {
        stack.push(uToken);
    }
    else {
        while(!stack.empty() && stack.top()->isOperator()) {
            out.push_back(tokenCast_ptr<EvaluableToken>(stack.top()));
            stack.pop();
        }

        if(stack.empty() || (stack.top()->str() != BasicCharacters::LPAR)) {
            throw SyntaxError("Syntax Error : Mismatched parentheses, missing "
                              "\"(\" parenthese");
        }
        else {
            stack.pop();
        }
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
    return ((tokens.size() >= 3)
            && (tokens[0] == token)
            && (tokens[1]->str() == string(1, Operators::SET)));
}

bool validOperator(const Operator_ptr& ope,
    const vector<AbstractToken_ptr>& tokens,
    const unsigned int currentIndex){
    auto valid = false;
    auto nextIndex = currentIndex + 1;

    if(ope->isUnary()) {
        valid = (tokens.size() > 1)
                && (nextIndex < tokens.size())
                && (!tokens[nextIndex]->isOperator());

    }
    else {
        valid = (tokens.size() > 1)
                && (currentIndex != 0)
                && (nextIndex < tokens.size());

        if(nextIndex < tokens.size()) {
            auto& nextToken = tokens[nextIndex];

            if(nextToken->isOperator()) {
                valid = valid && (tokenCast_ptr<Operator>(nextToken)->isUnary());
            }
        }
    }
    return valid;
}

}

vector<EvaluableToken_ptr> ExprParser::parse(const vector<AbstractToken_ptr>& tokens) {
    stack<AbstractToken_ptr> stack;
        vector<EvaluableToken_ptr> out;

        for(unsigned int i = 0; i < tokens.size(); ++i) {
            auto& token = tokens[i];
            //cout << *token << endl;

            if(token->isValue()) {
                if(token->isID() && !isVariableDefinition(tokens, token)) {
                    ExprApp::setVariable(tokenCast_ptr<ID>(token));
                }

                out.push_back(tokenCast_ptr<EvaluableToken>(token));
            }
            else if(token->isOperator()) {
                auto op = tokenCast_ptr<Operator>(token);
                if(validOperator(op, tokens, i)) {
                    parseOperator(tokenCast_ptr<Operator>(token), stack, out);
                }
                else {
                    throw SyntaxError("Syntax Error : Bad position/missing operand"
                                      " for operator \"" + op->str() + "\"");
                }
            }
            else parseBasicToken(tokenCast_ptr<BasicToken>(token), stack, out);
        }

        while(!stack.empty()) {
            auto remainingToken = stack.top();
            if(remainingToken->str() == BasicCharacters::LPAR) {
                throw SyntaxError("Syntax Error : Mismatched parentheses, missing "
                                  "\")\" parenthese");
            }
            else {
                out.push_back(tokenCast_ptr<EvaluableToken>(stack.top()));
                stack.pop();
            }
        }
        return out;
}

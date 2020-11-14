
#include "typealiases.hpp"
#include "exprparser.hpp"
#include "exprapp.hpp"
#include "error.hpp"
#include "function.hpp"
#include "constanttokens.hpp"
#include "utils.hpp"
#include "expr.hpp"

#include <vector>
#include <stack>

using namespace std;

namespace {

//bool isVariableDefinition(const std::vector<AbstractToken_ptr>& tokens,
//                          const AbstractToken_ptr& token) {
//    return ((tokens.size() >= 3)
//            && (tokens[0] == token)
//            && (tokens[1]->str() == string(1, Operators::SET)));
//}

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

namespace  {

    void parseValue(const AbstractToken_ptr& tok, TokenArray& out) {
        out.push_back(tok);
    }

    void parseVariadicFunction(Func_ptr& function, const TokenArray& tokens,
                               const unsigned int currentIndex) {
        TokenArray parseFirstArg;

        auto movingIndex = currentIndex + 2;
        auto LPARcount = 1;
        auto nbComma = 0;
        bool finished = false;

        while(movingIndex < tokens.size() && !finished) {
            auto tok = tokens[movingIndex];

            if(tok->type() == Type::LPAR) {
               ++LPARcount;
            }
            else if(tok->type() == Type::RPAR) {
               --LPARcount;
                if(LPARcount == 0) {
                    finished = true;
                }
            }
            else if(tok->type() == Type::COMMA) {
               if(LPARcount == 1) {
                   ++nbComma;
               }
            }

            if(finished) break;
            else ++movingIndex;
        }

        auto nbArgs = nbComma + 1;
        function->setNbArgs(nbArgs);
    }

    void parseFunc(const AbstractToken_ptr& tok,
                   TokenStack& stack, TokenArray& tokens,
                   unsigned int currentIndex) {

        stack.push(tok);

        auto func = tokenCast_ptr<Func>(tok);

        if(func->isVariadic()) {
            parseVariadicFunction(func, tokens, currentIndex);
        }
    }

    void parseID(const AbstractToken_ptr& tok, TokenArray& out) {
        out.push_back(tok);
    }

    void parseComma(TokenStack& stack, TokenArray& out) {
        while(!stack.empty() && (stack.top()->type() != Type::LPAR)) {
            out.push_back(topAndPop(stack));
        }

        if(stack.empty()) {
            throw SyntaxError("1Syntax Error : Mismatched parentheses, missing "
                              "\"(\" parenthese");
        }
    }

    void parseOperator(const AbstractToken_ptr& tok,
                       TokenStack& stack,
                       TokenArray& out,
                       const TokenArray& tokens,
                       unsigned int currentIndex) {

        auto op = tokenCast_ptr<Operator>(tok);

        if(!validOperator(op, tokens, currentIndex)) {
            throw SyntaxError("Syntax Error : Bad position/missing operand"
                                         " for operator \"" + op->str() + "\"");
        }

        while(!stack.empty() &&
              stack.top()->isOperator() &&
             (*tokenCast_ptr<Operator>(stack.top()) >= *op)){

            out.push_back(topAndPop(stack));
        }
        stack.push(op);
    }

    void parseLPar(const AbstractToken_ptr& tok, TokenStack& stack) {
        stack.push(tok);
    }

    void parseRPar(TokenStack& stack, TokenArray& out) {
        while(!stack.empty() && (stack.top()->type() != Type::LPAR)) {
            out.push_back(topAndPop(stack));
        }

        if(stack.empty()) { // not found the expected LPAR
            throw SyntaxError("2Syntax Error : Mismatched parentheses, missing "
                              "\"(\" parenthese");
        }

        stack.pop(); // pop the LPAR

        if(stack.top()->isFunc()) {
            out.emplace_back(topAndPop(stack));
        }
    }
}

TokenArray ExprParser::parse(TokenArray& tokens) {
    TokenArray out;
    TokenStack stack;

    for(unsigned int i = 0; i < tokens.size(); ++i) {
        auto& token = tokens[i];
        //PrintUtils::printStack(stack);
        //cout << endl;
        if(token->isValue()) {
            parseValue(token, out);
        }
        else if(token->isFunc()) {
            parseFunc(token, stack, tokens, i);
        }
        else if(token->isID() /*&& !isVariableDefinition(tokens, token)*/) {
            parseID(token, out);
        }
        else if(token->type() == Type::COMMA) {
            parseComma(stack, out);
        }
        else if(token->isOperator()) {
            parseOperator(token, stack, out, tokens, i);
        }
        else if(token->type() == Type::LPAR) {
            parseLPar(token,stack);
        }
        else if(token->type() == Type::RPAR) {
            parseRPar(stack, out);
        }
        else {
            throw SyntaxError("Error : Unknow Token \"" + token->str() +"\"");
        }
    }

    while(!stack.empty()) {
        auto remainingToken = stack.top();
        if(remainingToken->type() == Type::LPAR) {
            throw SyntaxError("Syntax Error : Mismatched parentheses, missing "
                              "\")\" parenthese");
        }
        else {
            out.push_back(topAndPop(stack));
        }
    }

    return out;
}

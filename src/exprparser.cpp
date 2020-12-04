
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

constexpr unsigned int NB_MIN_TOKENS_FOR_SET_COMMAND = 3;

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

bool currifiedDefinition(const Func_ptr& func,
                           const TokenArray& tokens) {
    return((tokens.size() >= NB_MIN_TOKENS_FOR_SET_COMMAND)
        && (tokens[1]->str().back() == Operators::SET)
        && Func::isValidForCurrying(*func));
}

}

namespace ParsingHandler  {

void parseConst(const AbstractToken_ptr& tok, TokenArray& out) {
    out.push_back(tok);
}

void parseFunc(const AbstractToken_ptr& funcPtr,
               TokenStack& stack,
               const TokenArray& tokens) {

    auto function = tokenCast_ptr<Func>(funcPtr);

    if (!currifiedDefinition(function, tokens) &&
        !Func::isDefined(*function)) {

        throw SyntaxError("Syntax Error : Function : \"" + function->str() +
                            "\" with " + to_string(function->nbArgs().value()) +
                            " arguments is not defined");
    }
    stack.push(funcPtr);
}

void parseID(const AbstractToken_ptr& tok, TokenArray& out) {
    out.push_back(tok);
}

void parseComma(TokenStack& stack, TokenArray& out) {
    while(!stack.empty() && (stack.top()->type() != Type::LPAR))
        out.push_back(topAndPop(stack));

    if(stack.empty())
        throw SyntaxError("Syntax Error : Mismatched parentheses, missing "
                          "\"(\" parenthese");
}

void parseOperator(const AbstractToken_ptr& tok,
                   TokenStack& stack,
                   TokenArray& out,
                   const TokenArray& tokens,
                   unsigned int currentIndex) {

    auto op = tokenCast_ptr<Operator>(tok);

    if(!validOperator(op, tokens, currentIndex))
        throw SyntaxError("Syntax Error : Bad position/missing operand"
                                     " for operator \"" + op->str() + "\"");
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
    while(!stack.empty() && (stack.top()->type() != Type::LPAR))
        out.push_back(topAndPop(stack));

    if(stack.empty())// not found the expected LPAR
        throw SyntaxError("Syntax Error : Mismatched parentheses, missing "
                          "\"(\" parenthese");
    stack.pop(); // pop the LPAR

    if(stack.empty() && out.empty())
        throw SyntaxError("Syntax Errror : Expected expression in ()");
    else if(!stack.empty() && stack.top()->isFunc())
        out.push_back(topAndPop(stack));
}

void parseSEMI(const AbstractToken_ptr& tok,
               const TokenArray& tokens){

    if(tok != tokens.back())
        throw SyntaxError("Syntax Error : SEMICOLON must be the last token"
                          " of a command");
    ExprApp::semiIsUsed = true;
}

}

TokenArray ExprParser::parse(const TokenArray& tokens) {
    TokenArray out;
    TokenStack stack;
    ExprApp::semiIsUsed = false;

    using namespace ParsingHandler;

    for(unsigned int i = 0; i < tokens.size(); ++i) {
        auto& token = tokens[i];

        switch(token->type()) {
            case Type::CONST :
                parseConst(token, out);
                break;

            case Type::PLACEHOLDER :
                parseConst(token, out);
                break;

            case Type::FUNC :
                parseFunc(token, stack, tokens);
                break;

            case Type::ID :
                parseID(token, out);
                break;

            case Type::COMMA :
                parseComma(stack, out);
                break;

            case Type::OPERATOR :
                parseOperator(token, stack, out, tokens, i);
                break;

            case Type::LPAR :
                parseLPar(token, stack);
                break;

            case Type::RPAR :
                parseRPar(stack, out);
                break;

            case Type::SEMI :
                parseSEMI(token, tokens);
                break;
        }
    }

    while(!stack.empty()) {
        auto remainingToken = stack.top();
        if(remainingToken->type() == Type::LPAR)
            throw SyntaxError("Syntax Error : Mismatched parentheses, missing "
                              "\")\" parenthese");
        else
            out.push_back(topAndPop(stack));
    }

    return out;
}

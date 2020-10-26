
#include <map>
#include <regex>

#include "exprlexer.hpp"
#include "value.hpp"
#include "binaryop.hpp"
#include "basictoken.hpp"
#include "syntaxerror.hpp"
#include "constants.hpp"
#include "unaryop.hpp"

using namespace std;
using namespace regex_constants;
using LexerAction = function<AbstractToken*(const string&)>;

const AbstractToken* previousToken = nullptr;

struct LexerRule {
    regex regex;
    LexerAction action;
};

namespace LexerActions {

const LexerAction createValue = [](const string& s) {
    return new Value(stod(s));
};

const LexerAction createOperator = [](const string& s) {
    AbstractToken* op;
    if((previousToken == nullptr)
       || previousToken->isOperator()
       || (previousToken->str() == BasicCharacters::LPAR)) {
        op = new UnaryOp(s.front());
    }
    else {
        op = new BinaryOp(s.front());
    }

    return op;
};

const LexerAction SCAN_LEXBUF = [](const string&) {
    return nullptr;
};

const LexerAction createLPAR = [](const string&) {
    return new LPAR();
};

const LexerAction createRPAR = [](const string&) {
    return new RPAR();
};

const LexerAction SYNTAX_ERROR = [](const string& s) {
    try {
        throw SyntaxError("Syntax Error : Unknow character \""
                          + s + "\" in exprlexer.cpp:28");
    }
    catch(SyntaxError& err) {
        cerr << err.what() << endl;
        exit(EXIT_FAILURE);
    }
    return nullptr;
};

}

using namespace LexerActions;

const vector<LexerRule> patterns {
    { regex("[0-9]+(\\.[0-9]+)?") , createValue          },
    { regex("(\\+|-|/|\\*)")      , createOperator       },
    { regex("\\(")                , createLPAR           },
    { regex("\\)")                , createRPAR           },
    { regex("\\s+")               , SCAN_LEXBUF          },
    { regex(".")                  , SYNTAX_ERROR         }
};

vector<AbstractToken*> ExprLexer::tokenize(const string& expr) {
    previousToken = nullptr;
    vector<AbstractToken*> tokenArray;
    auto it = expr.cbegin();

    while(it != expr.cend()) {
        for(const auto& [regex, action] : patterns) {
            smatch match;
            if(regex_search(it, expr.cend(), match, regex, match_continuous)) {
                auto res = action(match.str());

                if(res != nullptr) {
                    tokenArray.push_back(res);
                    previousToken = res;
                }

                it += match.str().length();
                break;
            }
        }
    }

    return tokenArray;
}


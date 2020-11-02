
#include <map>
#include <regex>

#include "exprlexer.hpp"
#include "unaryop.hpp"
#include "id.hpp"
#include "error.hpp"

using namespace std;
using namespace regex_constants;
using namespace Operators;
using LexerAction = function<AbstractToken_ptr(const string&)>;

static AbstractToken_ptr previousToken = nullptr;

struct LexerRule {
    regex reg_ex;
    LexerAction action;
};

namespace LexerActions {

const LexerAction createConst = [](const string& s) {
    return make_shared<Const>(stod(s));
};

const LexerAction createOperator = [](const string& s) {
    shared_ptr<AbstractToken> op;
    if(((previousToken == nullptr)
       || previousToken->isOperator()
       || (previousToken->str() == BasicCharacters::LPAR))
        &&((s[0] == ADD) || s[0] == MIN)){
        op = make_shared<UnaryOp>(s.front());
    }
    else {
        op = make_shared<BinaryOp>(s.front());
    }

    return  op;
};

const LexerAction SCAN_LEXBUF = [](const string&) {
    return nullptr;
};

const LexerAction createLPAR = [](const string&) {
    return make_shared<LPAR>();
};

const LexerAction createRPAR = [](const string&) {
    return make_shared<RPAR>();
};

const LexerAction createID = [](const string& s) {
    return make_shared<ID>(s);
};

const LexerAction LEXER_ERROR = [](const string& s) {
    throw LexerError("Lexer Error : Unknow character \""+ s + "\"");
    return nullptr;
};

}

using namespace LexerActions;

const vector<LexerRule> patterns {
    { regex("[0-9]+(\\.[0-9]+)?")           , createConst          },
    { regex("([a-zA-Z]|_)([a-zA-Z0-9]|_)*") , createID             },
    { regex("(\\+|-|/|=|\\*)")              , createOperator       },
    { regex("\\(")                          , createLPAR           },
    { regex("\\)")                          , createRPAR           },
    { regex("\\s+")                         , SCAN_LEXBUF          },
    { regex(".")                            , LEXER_ERROR         }
};

vector<AbstractToken_ptr> ExprLexer::tokenize(const string& expr)  {
    previousToken.reset();
    vector<AbstractToken_ptr> tokenArray;
    auto it = expr.cbegin();

    while(it != expr.cend()) {
        for(const auto& [reg_ex, action] : patterns) {
            smatch match;
            if(regex_search(it, expr.cend(), match, reg_ex, match_continuous)) {
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

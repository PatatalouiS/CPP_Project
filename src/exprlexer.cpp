
#include <map>
#include <regex>

#include "exprlexer.hpp"
#include "unaryop.hpp"
#include "binaryop.hpp"
#include "id.hpp"
#include "error.hpp"
#include "function.hpp"
#include "constanttokens.hpp"
#include "placeholder.hpp"

using namespace std;
using namespace regex_constants;
using namespace Operators;

struct LexerState {
    const string& expression;
    unsigned int currentIndex;
    string matchedString;
    TokenArray& out;
};

using LexerAction = function
    <AbstractToken_ptr(LexerState&)>;

struct LexerRule {
    regex reg_ex;
    LexerAction action;
};

namespace {

static constexpr char COMMA = ',';
static constexpr char LPAR = '(';
static constexpr char RPAR = ')';

AbstractToken_ptr previousToken = nullptr;

bool isUnaryOperator(const char c) {
    return (((previousToken == nullptr)
       || previousToken->isOperator()
       || (previousToken->type() == Type::LPAR)
       || (previousToken->type() == Type::COMMA))
        &&((c == ADD) || c == MIN));
}

pair<optional<unsigned int>, bool> getNbArgs(const string& expr,
                           const unsigned int lParIndex) {

    auto movingIndex = lParIndex + 1;
    auto LPARcount = 1;
    auto nbComma = 0;
    bool placeHolder = false;
    bool finished = false;

    if((movingIndex < expr.size()) && (expr[movingIndex] == RPAR))
        return { 0, false };

    while(movingIndex < expr.size() && !finished) {
        auto currentChar = expr[movingIndex];

        if(currentChar == LPAR) {
           ++LPARcount;
        }
        else if(currentChar == RPAR) {
           --LPARcount;
            if(LPARcount == 0)
                finished = true;
        }
        else if(currentChar == COMMA) {
           if(LPARcount == 1)
               ++nbComma;
        }
        else if(currentChar == '_') {
            if(LPARcount == 1)
                placeHolder = true;
        }

        ++movingIndex;
    }

    if(LPARcount != 0)
        return { nullopt, placeHolder };

    return { nbComma + 1, placeHolder };
}

}

namespace LexerActions {

const LexerAction createConst = [](LexerState& state) {
    return make_shared<Const>(stod(state.matchedString));
};

const LexerAction createPlaceHolder = [](LexerState& state) {
    auto order = stoi(state.matchedString.substr(1, state.matchedString.size()));

    if(order <= 0) {
        throw LexerError("Lexer Error : placeholder cant' have value : "
                         + to_string(order) + ". PlaceHolder value must be"
                         + "stricty poisitive.");
    }

    return make_shared<PlaceHolder>(order);
};

const LexerAction createID = [](LexerState& state) {
    return make_shared<ID>(state.matchedString);
};

const LexerAction createFunc = [](LexerState& state) {
    auto nbArgs = getNbArgs(state.expression, state.currentIndex);
    auto func = make_shared<Func>(previousToken->str(), nbArgs.first);
    func->setPlaceHolder(nbArgs.second);
    state.out.back() = func;
    previousToken = func;
    return nullptr;
};

const LexerAction createOperator = [](LexerState& state) {
    auto operatorChar = state.matchedString.front();
    AbstractToken_ptr token;

    if(isUnaryOperator(operatorChar))
        token = make_shared<UnaryOp>(operatorChar);
    else if (operatorChar == Operators::SET)
        token = set;
    else
        token = make_shared<BinaryOp>(operatorChar);
    return token;
};

const LexerAction createLPAR = [](LexerState& state) {
    if((previousToken != nullptr) && previousToken->isID())
        createFunc(state);
    return lPar;
};

const LexerAction createRPAR = [](LexerState&) {
    return rPar;
};

const LexerAction createCOMMA = [](LexerState&) {
    return comma;
};

const LexerAction createSEMI = [](LexerState&) {
    return semi;
};

const LexerAction SCAN_LEXBUF = [](LexerState&) {
    return nullptr;
};

const LexerAction LEXER_ERROR = [](LexerState& state) {
    throw LexerError("Lexer Error : Unknow character \""+ state.matchedString + "\"");
    return nullptr;
};


}

using namespace LexerActions;

const vector<LexerRule> patterns {
    { regex("[0-9]+(\\.[0-9]+)?")              , createConst          },
    { regex("_[1-9]+")                         , createPlaceHolder    },
    { regex("([a-zA-Z])([a-zA-Z0-9])*")        , createID             },
    { regex("(\\+|-|/|=|\\*)")                 , createOperator       },
    { regex("\\(")                             , createLPAR           },
    { regex("\\)")                             , createRPAR           },
    { regex(",")                               , createCOMMA          },
    { regex("\\;")                             , createSEMI           },
    { regex("\\s+")                            , SCAN_LEXBUF          },
    { regex(".")                               , LEXER_ERROR          }
};

vector<AbstractToken_ptr> ExprLexer::tokenize(const string& expr)  {
    previousToken.reset();
    TokenArray tokenArray;
    auto it = expr.cbegin();
    // State initialisation
    LexerState state {
        expr,
        0,
        "",
        tokenArray
    };

    while(it != expr.cend()) {
        for(const auto& [reg_ex, action] : patterns) {
            smatch match;
            if(regex_search(it, expr.cend(), match, reg_ex, match_continuous)) {
                state.currentIndex = it - expr.begin();
                state.matchedString = match.str();
                auto res = action(state);

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

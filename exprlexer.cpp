#include "exprlexer.hpp"
#include "value.hpp"
#include "binaryop.hpp"
#include <regex>
#include <unordered_map>
#include "syntaxerror.hpp"
#include "basictoken.hpp"
#include <map>

using namespace std;
using LexerAction = function<AbstractToken*(const string&)>;

struct LexerRule {
    regex regex;
    LexerAction action;
};

//namespace {

//const LexerAction createValue = [
//};

//const LexerAction createBinaryOperator = [](const string& s) {
//    return new BinaryOp(s.front());
//};

//const LexerAction SCAN_LEXBUF = [](const string&) {
//    return nullptr;
//};

//const LexerAction syntaxError = [](const string& s) {
//    try {
//        throw SyntaxError("Syntax Error : Unknow character \"" + s + "\" in exprlexer.cpp:28");
//    }
//    catch(SyntaxError& err) {
//        cerr << err.what() << endl;
//        exit(EXIT_FAILURE);
//    }
//    return nullptr;
//};

//const unordered_map<string, LexerAction> patterns {
//    { "(+|-)?[0-9]+(\\.[0-9]+)?"  , createValue          },
//    { "(\\+|-|/|\\*)"             , createBinaryOperator },
//    { "\\s*"                      , SCAN_LEXBUF          },
//    { "."                         , syntaxError          }
//};

const std::vector<LexerRule> patterns {
    {
        regex("[0-9]+(\\.[0-9]+)?"),
        [](const string& s) {
            return new Value(stod(s));
        }
    },
    {
        regex("(\\+|-|/|\\*)"),
        [](const string& s) {
            return new BinaryOp(s.front());
        }
    },
    {
        regex("\\("),
        [](const string&) {
            return new LPAR();
        }
    },
    {
        regex("\\)"),
        [](const string&) {
            return new RPAR();
        }
    },
    {
        regex("\\s+"),
        [](const string&) {
            return nullptr;
        }
    },
    {
        regex("."),
        [](const string& s) {
            try {
                throw SyntaxError("Syntax Error : Unknow character \""
                                  + s + "\" in exprlexer.cpp:28");
            }
            catch(SyntaxError& err) {
                cerr << err.what() << endl;
                exit(EXIT_FAILURE);
            }
            return nullptr;
        }
    }
};



template <typename K, typename V>
vector<V> mapToVector (map<K,V>& m) {
    vector<V> res;
    transform(m.begin(), m.end(), back_inserter(res), [] (auto& pair) {
        return pair.second;
    });

    return res;
}

vector<AbstractToken*> ExprLexer::tokenize(const string& expr) {
    string exprCopy(expr);
   // map<unsigned int, Token*> tokenMap;

//    for(auto& [regexStr, action] : patterns) {
//        regex regex(regexStr);
    //        auto begin = sregex_iterator(expr.begin(), expr.end(), regex);
    //        auto end = sregex_iterator();

//        for (auto it = begin; it != end; ++it ) {
//            auto res = action(it->str());
//            if(res != nullptr) {
//                tokenMap[ it->position() ] = action(it->str());
//            }
//        }
//    }

    vector<AbstractToken*> tokenArray;

    while(exprCopy != "") {
        for(auto& [regex, action] : patterns) {
            smatch match;
            if(regex_search(exprCopy, match, regex,
                            regex_constants::match_continuous)) {
                auto res = action(match.str());
                if(res != nullptr) {
                    tokenArray.push_back(res);
                }
                exprCopy = exprCopy.substr(match.str().length());
                break;
            }
        }
    }

    return tokenArray;
}


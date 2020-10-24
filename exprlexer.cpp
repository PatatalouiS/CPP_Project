#include "exprlexer.hpp"
#include "value.hpp"
#include "binaryop.hpp"
#include <regex>
#include <unordered_map>
#include <map>

using namespace std;
using LexerAction = function<Token*(const string&)>;

namespace {

const LexerAction createValue = [](const string& s) {
    return new Value(stod(s));
};

const LexerAction createBinaryOperator = [](const string& s) {
    return new BinaryOp(s.front());
};

const unordered_map<string, LexerAction> patterns {
    { "[0-9]+"        , createValue          },
    { "(\\+|-|/|\\*)" , createBinaryOperator }
};

template <typename K, typename V>
vector<V> mapToVector (map<K,V>& m) {
    vector<V> res;
    transform(m.begin(), m.end(), back_inserter(res), [] (auto& pair) {
       return pair.second;
    });

    return res;
}

}

vector<Token*> ExprLexer::tokenize(const string& expr) {
    map<unsigned int, Token*> tokenMap;

    for(auto& [regexStr, action] : patterns) {
        regex regex(regexStr);
        auto begin = sregex_iterator(expr.begin(), expr.end(), regex);
        auto end = sregex_iterator();

        for (auto it = begin; it != end; ++it ) {
            tokenMap[ it->position() ] = action(it->str());
        }
    }

    return mapToVector(tokenMap);
}


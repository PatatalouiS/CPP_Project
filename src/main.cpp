
#include "expr.hpp"
#include "exprapp.hpp"
#include "exprlexer.hpp"
#include "exprparser.hpp"
#include "tree.hpp"

using namespace std;

int main() {

//    auto a = ExprParser::parse(ExprLexer::tokenize("="));

//    for(auto& b : a) {
//        cout << *b << endl;
//    }

    ExprApp::run();
    return 0;
}


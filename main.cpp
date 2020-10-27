
#include "expr.hpp"
#include "exprapp.hpp"
#include "exprlexer.hpp"
#include "exprparser.hpp"

using namespace std;

int main() {

//    auto a = ExprParser::parse(ExprLexer::tokenize("walid - 5"));

//    for(auto b : a) {
//        cout << *b << endl;
//    }
    //ExprApp::run();

    Expr expr("walid = -(3 + 5) * -6");
    cout << expr.eval() << endl;

    Expr expr2("walid - 5");
    cout << expr2.eval() << endl;
    return 0;
}

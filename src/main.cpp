
#include "expr.hpp"
#include "exprapp.hpp"
#include "exprlexer.hpp"
#include "exprparser.hpp"
#include "utils.hpp"

using namespace std;


int main() {
    //ExprApp::run();

    string expr("lerp(0.5,0,1)");

    ExprParser p;

    auto a = ExprLexer::tokenize(expr);


    for(auto& b : a) {
        cout << *b << endl;
    }
    cout << endl;

    auto b = p.parse(a);

    for(auto& c : b) {
        cout << *c << endl;
    }

    cout << Expr(expr).eval() << endl;

    return 0;
}



#include "expr.hpp"
#include "exprapp.hpp"
#include "exprlexer.hpp"
#include "exprparser.hpp"
#include "utils.hpp"

using namespace std;


int main() {
    //ExprApp::run();
    string expr("polynome(sqrt(4), cos(0) * 1, 1, 0 + 1, 1 + 1 ) * -2 ");

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

   //cout <<  Expr("mama").eval() << endl;

    return 0;
}



#include "expr.hpp"
#include "exprapp.hpp"
#include "exprlexer.hpp"
#include "exprparser.hpp"
#include "utils.hpp"

using namespace std;

int main() {
    ExprApp::run();

//    auto a = ExprLexer::tokenize("caca = 3 + 5");

//    for(auto& t : a) {
//        cout << *t << endl;
//    }

//    string a ("square = pow(_1, 2)");
//    auto z = ExprLexer::tokenize(a);

//    for(auto& t : z) {
//        cout << *t << endl;
//    }

    return 0;
}

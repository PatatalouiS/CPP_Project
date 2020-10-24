
#include <iostream>
#include "value.hpp"
#include "binaryop.hpp"
#include "exprlexer.hpp"
#include "exprparser.hpp"
#include "expr.hpp"
#include <regex>

using namespace std;

int main() {

    Expr expr("3 + 5 * 1 / 1.22");
    cout << expr.eval() << endl;
    expr.print();

//    regex regex("[0-9]+");
//    std::smatch m;
//    string a("22   3   4 a b");


//    while(regex_search(a, m, regex, regex_constants::match_continuous)) {
//        cout << m.str() << endl;
//        a = a.substr(m.str().length());
//    }



    return 0;
}

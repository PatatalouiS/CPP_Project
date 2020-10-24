
#include <iostream>
#include "value.hpp"
#include "binaryop.hpp"
#include "exprlexer.hpp"
#include "exprparser.hpp"
#include "expr.hpp"

using namespace std;

int main() {

    Expr expr("3 + 2 * 4");
    cout << expr.eval() << endl;
    expr.print();

    return 0;
}

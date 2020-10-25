
#include <iostream>
#include "value.hpp"
#include "binaryop.hpp"
#include "exprlexer.hpp"
#include "exprparser.hpp"
#include "expr.hpp"
#include <regex>

using namespace std;

int main() {

    Expr expr("(3 + 5) * 6");
    cout << expr.eval() << endl;

    return 0;
}

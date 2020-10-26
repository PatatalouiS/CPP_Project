
#include <iostream>
#include "value.hpp"
#include "binaryop.hpp"
#include "exprlexer.hpp"
#include "exprparser.hpp"
#include "expr.hpp"
#include <regex>
#include <stack>



using namespace std;

void printStack2(stack<EvaluableToken*> s) {
    cout << endl << "PRINT_STACK" << endl;
    while(!s.empty()) {
         cout << *s.top() << " | ";
         s.pop();
    }
    cout << endl << endl;
}

void printVec2(const vector<EvaluableToken*>& s) {
    cout << endl << "PRINT_VEC" << endl;
    for(auto& i : s) {
        cout << *i << " | ";
    }
    cout << endl << endl;
}

int main() {

    Expr expr("");
    cout << expr.eval() << endl;


    return 0;
}

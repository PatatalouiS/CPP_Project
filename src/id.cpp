#include "id.hpp"
#include "exprapp.hpp"
#include "error.hpp"
#include "typealiases.hpp"

#include <exception>

using namespace std;

ValueExpr ID::eval(stack<AbstractToken_ptr>&) const {
    try {
        return ExprApp::getVariable(_id);
    }
    catch(NoDefError& err) {
        throw EvalError(err.what());
    }
}

void ID::print(std::ostream &out) const {
    out <<  "ID(" << _id;

    if(_value)
        out << "," << " " <<*_value;

    out << ")";
}

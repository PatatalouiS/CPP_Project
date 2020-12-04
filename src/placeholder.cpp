#include "placeholder.hpp"
#include "error.hpp"

using namespace std;

PlaceHolder::PlaceHolder(const unsigned int order) :
    AbstractToken(Type::PLACEHOLDER),
    _order(order)
{}

string PlaceHolder::str() const {
    return string("_").append(to_string(_order));
}

void PlaceHolder::print(std::ostream &out) const {
    out << "PlaceHolder(" + str() + ")";
}

ValueExpr PlaceHolder::eval(std::stack<AbstractToken_ptr> &) const {
    return _order;
}

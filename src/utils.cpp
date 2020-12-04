#include "utils.hpp"

using namespace std;

ostream& operator<< (ostream& out, const FuncResult& r) {
    out << "Function : " << r.first << endl;

    out << "Type : ";

    if(r.second.variadic){
        out << "Variadic";
    }
    else {
        out << "( ";

        for(unsigned int i = 0; i < r.second.nbArgs -1; ++ i) {
            out <<  "val * ";
        }

        out << "val ) -> val";
    }
    return out;
}

ostream& operator<< (ostream& out, const ValueExpr& val) {
    visit([&out](const auto& val) {
        out << val;
    }, val);
    return out;
}

#include "id.hpp"

#include <exception>

using namespace std;

double ID::eval(const double &, const double &) const {
    try {
        if(!_value) {
            throw bad_optional_access();
        }
    }
    catch(exception& err) {
        cerr << err.what();
        exit(EXIT_FAILURE);
    }

    return *_value;
}

void ID::print(std::ostream &out) const {
    out <<  "ID(" << _id << ", ";

    if(!_value) {
        out << "NO_VALUE";
    }
    else {
        out << *_value;
    }
    out << ")";
}

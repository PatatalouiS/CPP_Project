#include "operator.hpp"

bool Operator::operator>=(const Operator& other) const {
//        return !(((_symbol == '-') || (_symbol == '+')) &&
//                   ((other._symbol == '/') || (other._symbol == '*')));

    return precedence() >= other.precedence();
}

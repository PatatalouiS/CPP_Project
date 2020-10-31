#include "operator.hpp"

bool Operator::operator>=(const Operator& other) const {
    return precedence() >= other.precedence();
}

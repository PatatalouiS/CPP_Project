#include "exprtoken.h"

ExprToken::ExprToken(const std::string& s) : token(s) {
}

bool ExprToken::isOperator() const {
    for(const auto& op : OPERATORS) {
        if(op == token) {
            return true;
        }
    }
    return false;
}


bool ExprToken::isPriority(const ExprToken &other) const {
    auto otherStr = other.getStr();
    return(((token == MULTIPLY) || (token == DIVIDE)) &&
           ((otherStr == PLUS) || (otherStr == MINUS)));
}

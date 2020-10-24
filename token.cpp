
//#include "token.h"
//#include <iostream>

//using namespace std;


//Token::Token(const TokenValue& value) : _value{value} {
//    cout << "Token : constructor called" << endl;
//}

//Token::Token(const TokenValue&& value) : _value{value} {
//    cout << "Token : Move constructor called" << endl;
//}



////bool ExprToken::isOperator() const {
////    for(const auto& op : OPERATORS) {
////        if(op == token) {
////            return true;
////        }
////    }
////    return false;
////}


////bool ExprToken::isPriority(const ExprToken &other) const {
////    auto otherStr = other.getStr();
////    return(((token == MULTIPLY) || (token == DIVIDE)) &&
////           ((otherStr == PLUS) || (otherStr == MINUS)));
////}

//ostream& operator<< (ostream& out, const Operator op) {
//    out << static_cast<char>(op);
//    return out;
//}


//ostream& operator<< (ostream& out, const Token& token) {
//    visit([&out](const auto& tokenValue) {
//        out << tokenValue;
//    }, token._value);
//    return out;
//}

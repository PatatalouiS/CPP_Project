#ifndef EXPRTOKEN_H
#define EXPRTOKEN_H

#include <string>
#include <array>

const std::string PLUS{"+"};
const std::string MINUS{"-"};
const std::string MULTIPLY{"*"};
const std::string DIVIDE{"/"};

const std::array<std::string, 4> OPERATORS {
    PLUS, MINUS, MULTIPLY, DIVIDE
};


class ExprToken {

    private:

        std::string token;

    public:

       ExprToken(const std::string& s);

       bool isOperator() const;

       bool isPriority(const ExprToken& other) const;

       inline const std::string& getStr() const {
           return token;
       }
};

#endif // EXPRTOKEN_H

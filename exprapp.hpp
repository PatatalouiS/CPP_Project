#ifndef EXPRAPP_HPP
#define EXPRAPP_HPP

#include <unordered_map>

using Memory = std::unordered_map<std::string, double>;

class ExprApp {

    public:

        static void run();

        static void putVariable(const std::pair<std::string, double>& var);



        static Memory memory;
};

#endif // EXPRAPP_HPP

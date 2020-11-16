#ifndef EXPRAPP_HPP
#define EXPRAPP_HPP

#include <memory>
#include <unordered_map>
#include "id.hpp"

using Memory = std::unordered_map<std::string, double>;

class ExprApp {

    public:

        static void run();

        static void putVariable(const std::pair<std::string, double>& var);

        static double getVariable(const std::string& name);

        static bool isDefined(const std::string& name);

        static bool semiIsUsed;

    private:

        static const std::string PROMPT;

        static Memory memory;
};

#endif // EXPRAPP_HPP

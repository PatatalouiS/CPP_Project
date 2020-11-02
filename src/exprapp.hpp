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

        static void setVariable(const std::shared_ptr<ID>& tokenId);

        static Memory memory;
};

#endif // EXPRAPP_HPP

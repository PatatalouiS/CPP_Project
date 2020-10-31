#ifndef EXPRLEXER_H
#define EXPRLEXER_H

#include <vector>

#include "abstracttoken.hpp"
#include "typealiases.hpp"

class ExprLexer {

    public:

        static std::vector<AbstractToken_ptr> tokenize(const std::string& str);
};

#endif // EXPRLEXER_H

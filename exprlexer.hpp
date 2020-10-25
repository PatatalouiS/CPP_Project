#ifndef EXPRLEXER_H
#define EXPRLEXER_H

#include <vector>

#include "evaluabletoken.hpp"

class ExprLexer {

    public:

        static std::vector<AbstractToken*> tokenize(const std::string& str);

};

#endif // EXPRLEXER_H

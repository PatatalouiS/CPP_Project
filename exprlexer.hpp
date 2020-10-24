#ifndef EXPRLEXER_H
#define EXPRLEXER_H

#include <vector>

#include "token.hpp"

class ExprLexer {

    public:

        static std::vector<Token*> tokenize(const std::string& str);

};

#endif // EXPRLEXER_H

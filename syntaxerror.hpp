#ifndef SYNTAXERROR_HPP
#define SYNTAXERROR_HPP

#include <string>

class SyntaxError {

    public:

        SyntaxError(const std::string& str);

        virtual const std::string& what() const;

    private:

        std::string _msg;
};

#endif // SYNTAXERROR_HPP

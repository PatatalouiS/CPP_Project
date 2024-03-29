#ifndef BASICTOKEN_HPP
#define BASICTOKEN_HPP

#include "abstracttoken.hpp"
#include "constants.hpp"
#include "error.hpp"

class BasicToken : public AbstractToken {

    public:

        BasicToken(const Type type) :
            AbstractToken(type)
        {};

        virtual std::string str() const override = 0;

        ValueExpr eval(std::stack<AbstractToken_ptr> &) const override final {
            throw EvalError("This token is not evaluable");
        };

        inline void print(std::ostream& out) const override final { out << str(); }

        virtual ~BasicToken() = default;
};

#endif // UNSEMANTICTOKEN_HPP

#ifndef LPAR_HPP
#define LPAR_HPP

class LPAR : public BasicToken {
    public :
        inline LPAR() : BasicToken(Type::LPAR) {};
        inline std::string str() const override final { return BasicCharacters::LPAR; };
};

#endif //LPAR HPP

#ifndef RPAR_HPP
#define RPAR_HPP

class RPAR : public BasicToken {
    public :
        inline RPAR() : BasicToken(Type::RPAR) {};
        inline std::string str() const override final { return BasicCharacters::RPAR; };
};

#endif  //RPAR_HPP

#ifndef COMMA_HPP
#define COMMA_HPP

class COMMA : public BasicToken {
    public :
        inline COMMA() : BasicToken(Type::COMMA) {};
        inline std::string str() const override final { return BasicCharacters::COM; };
};

#endif  //COMMA_HPP

#ifndef SEMI_HPP
#define SEMI_HPP

class SEMI : public BasicToken {
    public :
        inline SEMI() : BasicToken(Type::SEMI) {};
        inline std::string str() const override final { return BasicCharacters::SEMI; };
};

#endif  //COMMA_HPP

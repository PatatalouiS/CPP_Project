#ifndef PLACEHOLDER_HPP
#define PLACEHOLDER_HPP

#include "abstracttoken.hpp"


class PlaceHolder : public AbstractToken
{
    public :

        PlaceHolder(const unsigned int value);

        std::string str() const override;

        inline bool isPlaceHolder() const override { return true; }

        void print(std::ostream &out) const override;

        virtual ValueExpr eval(std::stack<AbstractToken_ptr> &stack) const override;

        inline unsigned int order() const { return _order; }

    private :

        unsigned int _order;
};

#endif // PLACEHOLDER_HPP

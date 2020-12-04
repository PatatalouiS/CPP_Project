#ifndef CONSTANTTOKENS_HPP
#define CONSTANTTOKENS_HPP

#include "basictoken.hpp"
#include "setoperator.hpp"
#include <memory>

const std::shared_ptr<AbstractToken> lPar  = std::make_shared<LPAR>();
const std::shared_ptr<AbstractToken> rPar  = std::make_shared<RPAR>();
const std::shared_ptr<AbstractToken> comma = std::make_shared<COMMA>();
const std::shared_ptr<AbstractToken> semi  = std::make_shared<SEMI>();
const std::shared_ptr<AbstractToken> set   = std::make_shared<SetOperator>();


#endif // CONSTANTTOKENS_HPP

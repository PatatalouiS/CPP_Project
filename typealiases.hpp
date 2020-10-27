#ifndef TYPEALIASES_HPP
#define TYPEALIASES_HPP

#include "value.hpp"
#include "binaryop.hpp"
#include "basictoken.hpp"

using AbstractToken_ptr = std::shared_ptr<AbstractToken>;
using EvaluableToken_ptr = std::shared_ptr<EvaluableToken>;
using BasicToken_ptr = std::shared_ptr<BasicToken>;
using Operator_ptr = std::shared_ptr<Operator>;
using Value_ptr = std::shared_ptr<Value>;


#endif // TYPEALIASES_HPP

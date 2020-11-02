#ifndef TYPEALIASES_HPP
#define TYPEALIASES_HPP

#include "value.hpp"
#include "binaryop.hpp"
#include "basictoken.hpp"
#include "const.hpp"
#include <memory>

using AbstractToken_ptr = std::shared_ptr<AbstractToken>;
using EvaluableToken_ptr = std::shared_ptr<EvaluableToken>;
using BasicToken_ptr = std::shared_ptr<BasicToken>;
using Operator_ptr = std::shared_ptr<Operator>;
using Value_ptr = std::shared_ptr<Value>;
using Const_ptr = std::shared_ptr<Const>;

#endif // TYPEALIASES_HPP

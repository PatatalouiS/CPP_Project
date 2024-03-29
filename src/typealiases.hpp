#ifndef TYPEALIASES_HPP
#define TYPEALIASES_HPP

#include "function.hpp"
#include "basictoken.hpp"
#include "operator.hpp"
#include "const.hpp"
#include "id.hpp"

#include <memory>
#include <vector>
#include <stack>

class Func;

using AbstractToken_ptr = std::shared_ptr<AbstractToken>;
using BasicToken_ptr = std::shared_ptr<BasicToken>;
using Operator_ptr = std::shared_ptr<Operator>;
using Const_ptr = std::shared_ptr<Const>;
using Func_ptr = std::shared_ptr<Func>;
using ID_ptr = std::shared_ptr<ID>;

using TokenArray = std::vector<AbstractToken_ptr>;
using TokenStack = std::stack<AbstractToken_ptr>;

#endif // TYPEALIASES_HPP

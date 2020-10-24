#ifndef TYPEALIASES_HPP
#define TYPEALIA

#include "value.hpp"
#include "binaryop.hpp"

using TokenPtr = std::unique_ptr<Token>;
using ValuePtr = std::unique_ptr<Value>;
using BinaryOpPtr = std::unique_ptr<BinaryOp>;

#endif // TYPEALIASES_HPP

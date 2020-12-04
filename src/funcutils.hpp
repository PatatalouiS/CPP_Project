#ifndef FUNCUTILS_HPP
#define FUNCUTILS_HPP

#include <functional>
#include <vector>
#include <unordered_map>

using Args = std::vector<double>;
using ComputeHandler = std::function<double(const Args&)>;

struct FunctionDescriptor {
    unsigned int nbArgs;
    bool variadic;
    ComputeHandler fct;
};

using FunctionMapper = std::unordered_map<std::string, FunctionDescriptor>;

using FuncResult = std::pair<std::string, FunctionDescriptor>;

#endif // FUNCUTILS_HPP

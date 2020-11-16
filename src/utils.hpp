#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <memory>
#include <stack>
#include "typealiases.hpp"

template<typename T>
void printVector(const std::vector<std::shared_ptr<T>> v) {
    for(auto& i : v) {
        std::cout << *i << std::endl;
    }
}

template<typename T>
void printStack(const std::stack<std::shared_ptr<T>> v) {
    auto copy = v;
    std::cout << "___PRINT____" << std::endl;
    while(!copy.empty()) {
        std::cout << *copy.top() << std::endl;
        copy.pop();
    }
    std::cout << "___END____" << std::endl;
}

template<typename T>
T topAndPop(std::stack<T>& stack) {
    auto val = stack.top();
    stack.pop();
    return val;
}

template <typename T>
T backAndPop(std::vector<T>& vector) {
    auto val = vector.back();
    vector.pop_back();
    return val;
}


template <typename T>
std::shared_ptr<T> tokenCast_ptr(AbstractToken_ptr token) {
    return std::static_pointer_cast<T>(token);
}



#endif // UTILS_HPP

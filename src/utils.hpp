#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <memory>
#include "typealiases.hpp"

namespace PrintUtils {

template<typename T>
void printVector(const std::vector<std::shared_ptr<T>> v) {
    for(auto& i : v) {
        std::cout << *i << std::endl;
    }
}

}


#endif // UTILS_HPP

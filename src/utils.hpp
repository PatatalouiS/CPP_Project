#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>



namespace PrintUtils {

template<typename T>
void printVector(const std::vector<std::shared_ptr<T>> v) {
    for(auto& i : v) {
        std::cout << *i << std::endl;
    }
}

}

namespace InputUtils {

void read_nonblock_mode();

void read_block_mode();

bool pipe_is_used();

}

#endif // UTILS_HPP

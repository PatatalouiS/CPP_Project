#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>



namespace PrintUtils {

template<typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T*>& v) {
    for(const auto& el : v) {
        out << *el;
    }
    return out;
}

}

namespace InputUtils {

void read_nonblock_mode();

void read_block_mode();

bool pipe_is_used();

}

#endif // UTILS_HPP

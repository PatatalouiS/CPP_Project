#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <iostream>

namespace PrintUtils {

template<typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T*>& v) {
    for(const auto& el : v) {
        out << *el;
    }
    return out;
}

}

#endif // UTILS_HPP

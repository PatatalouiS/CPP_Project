
#include "utils.hpp"

namespace {

    const int flags = fcntl(0, F_GETFL, 0);

}

void InputUtils::read_nonblock_mode() {
    fcntl(0, F_SETFL, flags | O_NONBLOCK);
}

void InputUtils::read_block_mode() {
    fcntl(0, F_SETFL, flags);
}

bool InputUtils::pipe_is_used() {
    char a;
    read_nonblock_mode();
    bool pipedExec = read(STDIN_FILENO, &a, 1) == 1;
    read_block_mode();

    if(pipedExec) {
        std::cin.putback(a);
    }
    return pipedExec;
}

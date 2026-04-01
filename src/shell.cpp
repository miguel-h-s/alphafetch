#include <cstdlib>
#include <string>

std::string get_shell() {
    char* shell = std::getenv("SHELL");
    if (shell != nullptr) {
        return shell;
    }
    return "\033[1;31mBRUH\033[0m";
}
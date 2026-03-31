#include <cstdlib>
#include <string>

std::string get_shell() {
    char* shell = std::getenv("SHELL");
    if (shell != nullptr) {
        return shell;
    }
    return "SHELL = BRUH";
}
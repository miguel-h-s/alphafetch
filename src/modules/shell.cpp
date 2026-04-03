#include <cstdlib>
#include <string>

std::string get_shell() {
    const char* shell = std::getenv("SHELL");
    if (!shell) {
        return "unknown-shell";
    }

    std::string shell_str = shell;

    size_t pos = shell_str.find_last_of('/');
    if (pos != std::string::npos) {
        shell_str = shell_str.substr(pos + 1);
    }

    return shell_str.empty() ? "unknown-shell" : shell_str;
}
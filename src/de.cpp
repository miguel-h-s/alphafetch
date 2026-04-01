#include <string>
#include <cstdlib>

std::string get_wm() {
    char* wm = std::getenv("XDG_CURRENT_DESKTOP");
    if (wm == nullptr) {
        wm = std::getenv("DESKTOP_SESSION");
    }
    if (wm != nullptr) {
        return wm;
    }
    return "\033[1;31mBRUH\033[0m";
}
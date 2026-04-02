#include <cstdlib>
#include <string>

std::string get_terminal() {
    char* term = std::getenv("TERM_PROGRAM");
    if (term == nullptr) {
        term = std::getenv("TERM");
    }
    
    if (term != nullptr) {
        return term;
    }
    return "\033[1;31mBRUH\033[0m";
}
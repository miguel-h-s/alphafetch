#include <cstdlib>
#include <string>

std::string get_terminal() {
    char* term = std::getenv("TERM_PROGRAM");
    if (term == nullptr) {
        // Se não achar o program, tenta a variável clássica de emulação
        term = std::getenv("TERM");
    }
    
    if (term != nullptr) {
        return term;
    }
    return "TERMINAL = BRUH";
}
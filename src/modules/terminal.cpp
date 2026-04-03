#include <cstdlib>
#include <string>
#include <algorithm>

std::string clean_term(std::string term) {
    // remove sufixos
    size_t pos = term.find('-');
    if (pos != std::string::npos) {
        term = term.substr(0, pos);
    }

    
    std::transform(term.begin(), term.end(), term.begin(), ::tolower);

    return term;
}

std::string get_terminal() {
    const char* term = nullptr;

    // casos confiaveis
    term = std::getenv("TERM_PROGRAM"); 
    if (!term) term = std::getenv("KITTY_PID");   // kitty
    if (!term) term = std::getenv("ALACRITTY_LOG");// alacritty
    if (!term) term = std::getenv("TERM");        // fallback

    if (!term) {
        return "unknown-terminal";
    }

    std::string term_str = term;

    // casos especiais
    if (std::getenv("KITTY_PID")) return "kitty";
    if (std::getenv("KONSOLE_VERSION")) return "konsole";
    if (std::getenv("GNOME_TERMINAL_SCREEN")) return "gnome-terminal";
    if (std::getenv("WT_SESSION")) return "windows-terminal";

    return clean_term(term_str);
}
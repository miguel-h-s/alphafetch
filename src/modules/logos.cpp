#include "logos.hpp"
#include "colors.hpp"
#include <algorithm>

std::vector<std::string> get_ascii_art(const std::string& distro_name, int& width) {
    std::vector<std::string> art;
    
    
    std::string name_lower = distro_name;
    std::transform(name_lower.begin(), name_lower.end(), name_lower.begin(), ::tolower);

    using namespace Colors;

    if (name_lower.find("debian") != std::string::npos) {
        width = 14;
        art = {
            RED + "  _____       " + RESET, 
            RED + " /  __ \\      " + RESET, 
            RED + "|  /    |     " + RESET, 
            RED + "|  \\___-      " + RESET, 
            RED + "-_            " + RESET, 
            RED + "  --_         " + RESET  
        };
    }

    else if (name_lower.find("arch") != std::string::npos) {
        width = 14;
        art = {
            CYAN + "       /\\       " + RESET,
            CYAN + "      /  \\      " + RESET,
            CYAN + "     /    \\     " + RESET,
            CYAN + "    /      \\    " + RESET,
            CYAN + "   /   __   \\   " + RESET,
            CYAN + "  /   (  )   \\  " + RESET,
            CYAN + " / __/  \\__ \\ " + RESET,
            CYAN + "/__/      \\__\\" + RESET
        };
    }

    else {
        width = 14;
        art = {
            WHITE + "    .--.    " + RESET,
            WHITE + "   |o_o |   " + RESET,
            YELLOW + "   |:_/ |   " + RESET,
            WHITE + "  //   \\ \\  " + RESET,
            WHITE + " (|     | ) " + RESET,
            WHITE + "/'\\_   _/`\\ " + RESET,
            YELLOW + "\\___)=(___/" + RESET
        };
    }

    return art;
}
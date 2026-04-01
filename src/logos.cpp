#include "logos.hpp"
#include "colors.hpp"
#include <algorithm>

std::vector<std::string> get_ascii_art(const std::string& distro_name, int& width) {
    std::vector<std::string> art;
    
    // Converte para minúsculo para facilitar a comparação e evitar erros
    std::string name_lower = distro_name;
    std::transform(name_lower.begin(), name_lower.end(), name_lower.begin(), ::tolower);

    using namespace Colors;

    // 1. DEBIAN (Agora um Gatinho!)
    if (name_lower.find("debian") != std::string::npos) {
        width = 14;
        art = {
            CYAN + "   /\\_/\\      " + RESET,
            CYAN + "  ( o.o )     " + RESET,
            CYAN + "   > ^ <      " + RESET,
            CYAN + "    / \\       " + RESET,
            CYAN + "   (   )      " + RESET,
            CYAN + "    ^ ^       " + RESET,
            "              ", // Linhas vazias para manter o alinhamento
            "              "  // com as informações do lado direito
        };
    }
    // 2. ARCH LINUX
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
    // 3. PADRÃO (TUX / PINGUIM) para qualquer outra distro
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
#include "logos.hpp"
#include <algorithm>

std::vector<std::string> get_ascii_art(const std::string& distro_name, int& width) {
    std::vector<std::string> art;
    
    // Converte para minúsculo para facilitar a comparação e evitar erros
    std::string name_lower = distro_name;
    std::transform(name_lower.begin(), name_lower.end(), name_lower.begin(), ::tolower);

    // 1. DEBIAN
    if (name_lower.find("debian") != std::string::npos) {
        width = 14;
        art = {
            "  _____     ",
            " / ___ \\    ",
            "| |   | |   ",
            "| |   | |   ",
            "| |___| |   ",
            " \\_____/    ",
            "        \\   ",
            "         \\  "
        };
    }
    // 2. ARCH LINUX
    else if (name_lower.find("arch") != std::string::npos) {
        width = 14;
        art = {
            "       /\\       ",
            "      /  \\      ",
            "     /    \\     ",
            "    /      \\    ",
            "   /   __   \\   ",
            "  /   (  )   \\  ",
            " / __/  \\__ \\ ",
            "/__/      \\__\\"
        };
    }
    // 3. PADRÃO (TUX / PINGUIM) para qualquer outra distro
    else {
        width = 14;
        art = {
            "    .--.    ",
            "   |o_o |   ",
            "   |:_/ |   ",
            "  //   \\ \\  ",
            " (|     | ) ",
            "/'\\_   _/`\\ ",
            "\\___)=(___/"
        };
    }

    return art;
}
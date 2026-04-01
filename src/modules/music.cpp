#include "fetch.hpp"
#include <iostream>
#include <string>

std::string get_music() {
    // Pega o artista e o título da música atual usando um pipe rápido
    FILE* pipe = popen("playerctl metadata --format '{{ artist }} - {{ title }}' 2>/dev/null", "r");
    if (!pipe) return "Silêncio";

    char buffer[128];
    std::string result = "";
    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result = buffer;
    }
    pclose(pipe);

    // Remove a quebra de linha do final se ela existir
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    return result.empty() ? "Nada tocando" : result;
}
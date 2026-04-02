#include "fetch.hpp"
#include <iostream>
#include <string>

std::string get_music() {
    FILE* pipe = popen("playerctl metadata --format '{{ artist }} - {{ title }}' 2>/dev/null", "r");
    if (!pipe) return "Silêncio";

    char buffer[128];
    std::string result = "";
    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result = buffer;
    }
    pclose(pipe);

    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    return result.empty() ? "Nothing playing" : result;
}
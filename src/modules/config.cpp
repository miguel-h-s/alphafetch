#include "config.hpp"

#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>

#include "colors.hpp"

namespace Utils {
    std::string trim(const std::string& str) {
        const char* ws = " \t\n\r";

        size_t start = str.find_first_not_of(ws);
        if (start == std::string::npos) return "";

        size_t end = str.find_last_not_of(ws);
        return str.substr(start, end - start + 1);
    }

    std::string to_lower(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }
}

// configuração

void Config::load_config() {
    const char* home = std::getenv("HOME");
    if (!home) return;

    std::ifstream file(std::string(home) + "/.config/alphafetch/config.conf");
    if (!file) return;

    std::string line;

    while (std::getline(file, line)) {
        line = Utils::trim(line);

        if (line.empty() || line[0] == '#')
            continue;

        auto pos = line.find('=');
        if (pos == std::string::npos)
            continue;

        std::string key   = Utils::trim(line.substr(0, pos));
        std::string value = Utils::trim(line.substr(pos + 1));

        options[key] = value;
    }
}

// cores

std::string Config::get_color_ansi(const std::string& color_name) {
    static const std::unordered_map<std::string, std::string> color_map = {
        {"red", Colors::RED},
        {"green", Colors::GREEN},
        {"yellow", Colors::YELLOW},
        {"blue", Colors::BLUE},
        {"magenta", Colors::MAGENTA},
        {"cyan", Colors::CYAN},
        {"white", Colors::WHITE},

        {"b_red", Colors::B_RED},
        {"b_green", Colors::B_GREEN},
        {"b_yellow", Colors::B_YELLOW},
        {"b_blue", Colors::B_BLUE},
        {"b_magenta", Colors::B_MAGENTA},
        {"b_cyan", Colors::B_CYAN},
        {"b_white", Colors::B_WHITE}
    };

    std::string name = Utils::to_lower(color_name);

    auto it = color_map.find(name);
    return (it != color_map.end()) ? it->second : Colors::RESET;
}
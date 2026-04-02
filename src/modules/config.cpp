#include "config.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib> 
#include <algorithm>

#include "colors.hpp"
#include <map>
#include <string>


void Config::load_config() {
    const char* home = std::getenv("HOME");
    if (!home) return; 

    std::string path = std::string(home) + "/.config/alphafetch/config.conf";
    std::ifstream file(path);

    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Remove espaços do começo e do fim da linha
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        // Pula linhas vazias ou comentários
        if (line.empty() || line[0] == '#') {
            continue;
        }

        size_t delimiter_pos = line.find('=');
        if (delimiter_pos != std::string::npos) {
            std::string key = line.substr(0, delimiter_pos);
            std::string value = line.substr(delimiter_pos + 1);

            // Limpa espaços em volta da CHAVE (ex: "show_os " -> "show_os")
            key.erase(key.find_last_not_of(" \t\r\n") + 1);
            key.erase(0, key.find_first_not_of(" \t\r\n"));

            // Limpa espaços em volta do VALOR (ex: " true " -> "true")
            value.erase(0, value.find_first_not_of(" \t\r\n"));
            value.erase(value.find_last_not_of(" \t\r\n") + 1);

            // Salva a string limpa no mapa
            options[key] = value;
        }
    }

    file.close();
}

std::string Config::get_color_ansi(const std::string& color_name) {
    std::string name = color_name;
    for (auto &c : name) c = std::tolower(c);

    if (name == "red")       return Colors::RED;
    if (name == "green")     return Colors::GREEN;
    if (name == "yellow")    return Colors::YELLOW;
    if (name == "blue")      return Colors::BLUE;
    if (name == "magenta")   return Colors::MAGENTA;
    if (name == "cyan")      return Colors::CYAN;
    if (name == "white")     return Colors::WHITE;
    
    if (name == "b_red")     return Colors::B_RED;
    if (name == "b_green")   return Colors::B_GREEN;
    if (name == "b_yellow")  return Colors::B_YELLOW;
    if (name == "b_blue")    return Colors::B_BLUE;
    if (name == "b_magenta") return Colors::B_MAGENTA;
    if (name == "b_cyan")    return Colors::B_CYAN;
    if (name == "b_white")   return Colors::B_WHITE;

    return Colors::RESET; // Se não achar nenhuma ou for inválida
}
#include "config.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib> // Para getenv

void Config::load_config() {
    // 1. Descobrir onde fica a pasta HOME do usuário
    const char* home = std::getenv("HOME");
    if (!home) return; // Se não achar o home, cancela e usa os padrões

    std::string path = std::string(home) + "/.config/alphafetch/config.conf";
    std::ifstream file(path);

    // Se o arquivo não existir, não faz nada (o is_enabled vai retornar true por padrão)
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Remove espaços em branco sobrando
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        // Ignora linhas vazias ou que começam com #
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Divide a linha no sinal de '='
        size_t delimiter_pos = line.find('=');
        if (delimiter_pos != std::string::npos) {
            std::string key = line.substr(0, delimiter_pos);
            std::string value = line.substr(delimiter_pos + 1);

            // Limpa espaços em volta da chave e do valor
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));

            // Converte o valor para booleano
            bool bool_value = (value == "true");

            // Salva no nosso mapa!
            options[key] = bool_value;
        }
    }

    file.close();
}
#pragma once
#include <string>
#include <map>

// Estrutura para guardar as configurações
struct Config {
    // Mudamos de 'bool' para 'std::string' para aceitar cores também!
    std::map<std::string, std::string> options;

    // Função que vai ler o arquivo
    void load_config();

    // Função para buscar uma string (como a cor) com um valor padrão caso não exista
    std::string get_string(const std::string& key, const std::string& fallback = "") {
        if (options.find(key) != options.end()) {
            return options[key];
        }
        return fallback;
    }

    // Função para buscar o código ANSI da cor traduzido
    std::string get_color_ansi(const std::string& color_name);

    // Função auxiliar para checar se algo está ativo
    bool is_enabled(const std::string& key) {
        // Se a chave não existir no arquivo, o padrão continua sendo TRUE
        if (options.find(key) == options.end()) {
            return true; 
        }
        // Como agora guardamos tudo como texto, checamos se o texto é "true"
        return options[key] == "true";
    }
};
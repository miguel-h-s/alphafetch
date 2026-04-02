#pragma once
#include <string>
#include <map>

// Estrutura para guardar as configurações
struct Config {
    // Mapa para guardar as chaves e valores (ex: "show_music" -> true)
    std::map<std::string, bool> options;

    // Função que vai ler o arquivo
    void load_config();

    // Função auxiliar para checar se algo está ativo
    bool is_enabled(const std::string& key) {
        // Se a chave não existir no arquivo, o padrão é ser TRUE
        if (options.find(key) == options.end()) {
            return true; 
        }
        return options[key];
    }
};
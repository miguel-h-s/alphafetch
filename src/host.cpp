#include "fetch.hpp"
#include <unistd.h>
#include <fstream>
#include <iostream>

std::string get_user_host() {
    char hostname[1024];
    hostname[1023] = '\0';
    
    // Pega o hostname do sistema
    if (gethostname(hostname, 1023) != 0) {
        return "unknown@unknown"; // Falha de segurança/sistema
    }

    // Pega o usuário logado via variável de ambiente
    char* user = getenv("USER");
    std::string user_str = (user != nullptr) ? user : "unknown";

    // Retorna formatado com cores: usuario@host
    return c_green + c_bold + user_str + c_reset + "@" + c_green + c_bold + std::string(hostname) + c_reset;
}
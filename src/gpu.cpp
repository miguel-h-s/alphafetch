#include "fetch.hpp"
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <regex>

// Função auxiliar para executar comando e pegar a saída (você pode mover isso para um arquivo 'utils')
std::string exec_command(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string get_gpu_name() {
    try {
        // Comando lspci focado em adaptadores VGA, pegando apenas a linha relevante
        std::string raw_output = exec_command("lspci | grep -i vga");
        
        // Exemplo de saída: "00:02.0 VGA compatible controller: Intel Corporation UHD Graphics (rev 02)"
        
        // Usamos Regex para capturar tudo depois de "controller: " e antes de qualquer "("
        std::regex gpu_regex("controller: ([^(]+)");
        std::smatch match;

        if (std::regex_search(raw_output, match, gpu_regex) && match.size() > 1) {
            std::string gpu_name = match[1].str();
            
            // Remove espaços em branco extras no final (lspci às vezes deixa)
            gpu_name.erase(gpu_name.find_last_not_of(" \n\r\t") + 1);
            
            return gpu_name;
        } else {
            return "GPU NAME = BRUH";
        }
    } catch (...) {
        return "erro que nem sei dizer (Error)";
    }
}
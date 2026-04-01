#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Para std::max
#include "fetch.hpp"
#include "logos.hpp"
#include "colors.hpp" // Adicionando o cabeçalho de cores!

// Função auxiliar para pintar erros de vermelho automaticamente
std::string format_info(const std::string& label, const std::string& value) {
    using namespace Colors;
    
    // Se o valor contiver "BRUH", "Desconhecido" ou "Error", pintamos de vermelho negrito
    if (value.find("BRUH") != std::string::npos || 
        value == "Desconhecido" || 
        value == "Error") {
        return B_WHITE + label + RESET + B_RED + value + RESET;
    }
    
    // Caso contrário, imprime normal (Título em branco negrito e valor padrão)
    return B_WHITE + label + RESET + value;
}

int main() {
    using namespace Colors;

    // --- 1. ARTE EM ASCII ---
    std::string distro_atual = get_distro(); 
    int ascii_width = 0;
    
    // Puxa a arte certa baseada na distro detectada
    std::vector<std::string> ascii_art = get_ascii_art(distro_atual, ascii_width);

    // --- 2. COLETANDO AS INFORMAÇÕES ---
    
    // Primeira linha: user@host
    std::string user_host = get_user_host();
    
    // Separador (uma linha de traços)
    std::string separator = "";
    for(int i=0; i<20; ++i) separator += "-";

    
    // Lista de informações principais tratadas com a nossa função de cores
    std::vector<std::string> info = {
        format_info("OS:       ", get_distro()),
        format_info("Kernel:   ", get_kernel()),
        format_info("Uptime:   ", get_uptime()),
        format_info("Shell:    ", get_shell()),
        format_info("Packages: ", get_packages()),
        format_info("WM:       ", get_wm()),
        format_info("Terminal: ", get_terminal()),
        "", // Linha vazia separadora
        format_info("CPU:      ", get_cpu()),
        format_info("GPU:      ", get_gpu_name()),
        format_info("RAM:      ", get_ram()),
        format_info("Disk:     ", get_disk()),
        format_info("IP local:      ", get_local_ip()),
        format_info("Music:     ", get_music()),
        "", // Linha vazia separadora
        format_info("Theme:    ", get_gtk_theme()),
        format_info("Icons:    ", get_icon_theme()),
        format_info("Cursor:   ", get_cursor_theme()),
        format_info("Font:     ", get_font())
    };

    // --- 3. LOGICA DE IMPRESSÃO LADO A LADO ---

    size_t info_lines_count = info.size() + 2; // Total de linhas de informação
    size_t max_linhas = std::max(ascii_art.size(), info_lines_count);

    // Calcula quantas linhas de espaço em branco precisamos dar no topo da logo para centralizar
    size_t vertical_offset = 0;
    if (info_lines_count > ascii_art.size()) {
        vertical_offset = (info_lines_count - ascii_art.size()) / 2;
    }

    std::cout << std::endl; // Espaço no topo

    for (size_t i = 0; i < max_linhas; ++i) {
        
        std::cout << "  "; // Margem esquerda
        
        // A. Imprime a linha da arte ASCII (Centralizada Verticalmente)
        
        // Se estivermos dentro da janela onde a logo deve aparecer:
        if (i >= vertical_offset && (i - vertical_offset) < ascii_art.size()) {
            std::cout << ascii_art[i - vertical_offset];
        } else {
            // Caso contrário (muito no topo ou muito embaixo), imprime espaços
            for(int w=0; w < ascii_width; ++w) std::cout << " ";
        }

        std::cout << "   "; // Espaçamento central

        // C. Imprime a linha de informação
        if (i == 0) {
            std::cout << user_host;
        } 
        else if (i == 1) {
            std::cout << separator;
        } 
        else if ((i - 2) < info.size()) {
            std::cout << info[i - 2];
        }

        std::cout << std::endl; 
    }

    std::cout << std::endl << std::endl; // Espaço no final

    // --- 4. BLOCOS DE CORES ---
    std::cout << "  "; //margen esquerda
    
    // Cores normais (Fundo)
    for(int i = 40; i <= 47; ++i) {
        std::cout << "\033[" << i << "m   \033[0m";
    }
    std::cout << std::endl << "  "; // Pula linha e mantém a margem
    
    // Cores brilhantes (Fundo)
    for(int i = 100; i <= 107; ++i) {
        std::cout << "\033[" << i << "m   \033[0m";
    }
    std::cout << std::endl << std::endl;

    return 0;
}
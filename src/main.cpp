#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Para std::max
#include "fetch.hpp"
#include "logos.hpp"

int main() {
    // --- 1. ARTE EM ASCII ---
    std::string distro_atual = get_distro(); // Usa a função que você já tem!
    int ascii_width = 0;
    
    // Puxa a arte certa baseada na distro detectada
    std::vector<std::string> ascii_art = get_ascii_art(distro_atual, ascii_width);

    // --- 2. COLETANDO AS INFORMAÇÕES ---
    
    // Primeira linha: user@host
    std::string user_host = get_user_host();
    
    // Separador (uma linha de traços)
    std::string separator = "";
    // Precisamos calcular o tamanho real da string sem as cores ANSI para o separador.
    // Para simplificar agora, vamos usar um tamanho fixo.
    for(int i=0; i<20; ++i) separator += "-";

    // Lista de informações principais (sua lógica antiga, expandida)
    std::vector<std::string> info = {
        c_bold + "OS:       " + c_reset + get_distro(),
        c_bold + "Kernel:   " + c_reset + get_kernel(),
        c_bold + "Uptime:   " + c_reset + get_uptime(),
        c_bold + "Shell:    " + c_reset + get_shell(),
        c_bold + "WM:       " + c_reset + get_wm(),
        c_bold + "Terminal: " + c_reset + get_terminal(),
        "", // Linha vazia separadora
        c_bold + "CPU:      " + c_reset + get_cpu(),
        c_bold + "GPU:      " + c_reset + get_gpu_name(), // Nome comercial da GPU
        c_bold + "RAM:      " + c_reset + get_ram(),
        c_bold + "Disk:     " + c_reset + get_disk(),
        "", // Linha vazia separadora
        c_bold + "Theme:    " + c_reset + get_gtk_theme(), // GTK Theme
        c_bold + "Icons:    " + c_reset + get_icon_theme(), // Icons Theme
        c_bold + "Cursor:   " + c_reset + get_cursor_theme(), // Cursor Theme
        c_bold + "Font:     " + c_reset + get_font() // System Font
    };

    // --- 3. LOGICA DE IMPRESSÃO LADO A LADO ---

    // Descobrir qual dos dois vetores tem mais linhas para iterar
    // (Lembrando que user_host e separator são linhas fixas extras no topo do info)
    size_t info_lines_count = info.size() + 2; // + user_host, + separator
    size_t max_linhas = std::max(ascii_art.size(), info_lines_count);

    std::cout << std::endl; // Espaço no topo

    for (size_t i = 0; i < max_linhas; ++i) {
        
        // A. Imprime a linha da arte ASCII (com cor)
        std::cout << "  "; // Margem esquerda
        if (i < ascii_art.size()) {
            std::cout << c_cyan << ascii_art[i] << c_reset;
        } else {
            // Se a arte acabou, imprime espaços vazios para manter o alinhamento
            for(int w=0; w < ascii_width; ++w) std::cout << " ";
        }

        // B. Espaçamento central entre a arte e a informação
        std::cout << "   "; 

        // C. Imprime a linha de informação
        
        // Linha 0: user@host
        if (i == 0) {
            std::cout << user_host;
        } 
        // Linha 1: separador
        else if (i == 1) {
            std::cout << separator;
        } 
        // Linhas seguintes: lista de info (com offset de 2)
        else if ((i - 2) < info.size()) {
            std::cout << info[i - 2];
        }

        std::cout << std::endl; // Pula para a próxima linha
    }

    std::cout << std::endl << std::endl; // Espaço no final

    return 0;
}
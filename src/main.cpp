#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include "fetch.hpp"
#include "logos.hpp"
#include "colors.hpp" 
#include "config.hpp"

// Função para remover espaços em branco do final de uma string
std::string rtrim(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

// Atualizamos para receber as cores definidas pelo usuário no config
std::string format_info(const std::string& label, const std::string& value, const std::string& label_color, const std::string& value_color) {
    using namespace Colors;
    
    // Tratamento de erros mantém o padrão vermelho chamativo
    if (value.find("BRUH") != std::string::npos || 
        value == "Desconhecido" || 
        value == "Error") {
        return label_color + label + RESET + B_RED + value + RESET;
    }
    
    // Concatena usando as cores passadas por parâmetro
    return label_color + label + RESET + value_color + value + RESET;
}

int main(int argc, char* argv[]) {
    using namespace Colors;

    Config config;
    config.load_config();

    // 1. Puxando as cores configuradas ou definindo fallbacks (padrões)
    std::string label_color_str = config.get_string("color_label", "b_white");
    std::string value_color_str = config.get_string("color_value", "white");

    // 2. Traduzindo os nomes escritos para os códigos ANSI do seu colors.hpp
    std::string label_color = config.get_color_ansi(label_color_str);
    std::string value_color = config.get_color_ansi(value_color_str);

    std::string distro_atual = get_distro(); 
    int ascii_width = 0;
    
    // isto pega o nome de todas as distros
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg.length() > 1 && arg[0] == '-') {
            distro_atual = arg.substr(1); 
        }
    }

    std::vector<std::string> ascii_art = get_ascii_art(distro_atual, ascii_width);

    // FORÇAMOS a largura da logo para 45 colunas, ignorando o que veio do arquivo .txt
    int FIXED_LOGO_WIDTH = 45;

    std::string user_host = get_user_host();
    
    std::string separator = "";
    for(int i=0; i<20; ++i) separator += "-";

    std::vector<std::string> info;
    
    // 3. Repassando as cores para a função de formatação
    if (config.is_enabled("show_os"))       info.push_back(format_info(i_os      + "OS: ", get_distro(), label_color, value_color));
    if (config.is_enabled("show_kernel"))   info.push_back(format_info(i_kernel  + "Kernel: ", get_kernel(), label_color, value_color));
    if (config.is_enabled("show_uptime"))   info.push_back(format_info(i_uptime  + "Uptime: ", get_uptime(), label_color, value_color));
    if (config.is_enabled("show_shell"))    info.push_back(format_info(i_shell   + "Shell: ", get_shell(), label_color, value_color));
    if (config.is_enabled("show_packages")) info.push_back(format_info(i_pkgs    + "Packages: ", get_packages(), label_color, value_color));
    if (config.is_enabled("show_wm"))       info.push_back(format_info(i_wm      + "WM: ", get_wm(), label_color, value_color));
    if (config.is_enabled("show_terminal")) info.push_back(format_info(i_term    + "Terminal: ", get_terminal(), label_color, value_color));
    
    if (!info.empty()) info.push_back(""); 
    
    if (config.is_enabled("show_cpu"))      info.push_back(format_info(i_cpu     + "CPU: ", get_cpu(), label_color, value_color));
    if (config.is_enabled("show_gpu"))      info.push_back(format_info(i_gpu     + "GPU: ", get_gpu_name(), label_color, value_color));
    if (config.is_enabled("show_ram"))      info.push_back(format_info(i_ram     + "RAM: ", get_ram(), label_color, value_color));
    if (config.is_enabled("show_disk"))     info.push_back(format_info(i_disk    + "Disk: ", get_disk(), label_color, value_color));
    if (config.is_enabled("show_ip"))       info.push_back(format_info(i_ip      + "IP local: ", get_local_ip(), label_color, value_color));
    if (config.is_enabled("show_music"))    info.push_back(format_info(i_music   + "Music: ", get_music(), label_color, value_color));
    
    if (!info.empty()) info.push_back(""); 
    
    if (config.is_enabled("show_theme"))    info.push_back(format_info(i_theme   + "Theme: ", get_gtk_theme(), label_color, value_color));
    if (config.is_enabled("show_icons"))    info.push_back(format_info(i_icons   + "Icons: ", get_icon_theme(), label_color, value_color));
    if (config.is_enabled("show_cursor"))   info.push_back(format_info(i_cursor  + "Cursor: ", get_cursor_theme(), label_color, value_color));
    if (config.is_enabled("show_font"))     info.push_back(format_info(i_font    + "Font: ", get_font(), label_color, value_color));

    size_t info_lines_count = info.size() + 2; 
    size_t max_linhas = std::max(ascii_art.size(), info_lines_count);

    size_t vertical_offset = 0;
    if (info_lines_count > ascii_art.size()) {
        vertical_offset = (info_lines_count - ascii_art.size()) / 2;
    }

    std::cout << std::endl; 

    for (size_t i = 0; i < max_linhas; ++i) {
        std::cout << "  "; 
        
        int printed_chars = 0;
        
        if (i >= vertical_offset && (i - vertical_offset) < ascii_art.size()) {
            std::string logo_line = ascii_art[i - vertical_offset];
            std::string cleaned_line = rtrim(logo_line);
            
            std::cout << cleaned_line;
            printed_chars = cleaned_line.length();
        }

        for (int w = printed_chars; w < FIXED_LOGO_WIDTH; ++w) {
            std::cout << " ";
        }

        std::cout << "   "; 

        if (i == 0) {
            std::cout << user_host;
        } 
        else if (i == 1) {
            std::cout << separator;
        } 
        else if ((i - 2) < info.size()) {
            if (!info[i - 2].empty()) {
                std::cout << info[i - 2];
            }
        }

        std::cout << std::endl; 
    }

    std::cout << std::endl; 

    std::cout << "  "; 
    for(int i = 40; i <= 47; ++i) {
        std::cout << "\033[" << i << "m   \033[0m";
    }
    std::cout << std::endl << "  "; 
    
    for(int i = 100; i <= 107; ++i) {
        std::cout << "\033[" << i << "m   \033[0m";
    }
    std::cout << std::endl << std::endl;

    return 0;
}
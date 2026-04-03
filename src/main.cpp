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
    
    if (value.find("BRUH") != std::string::npos || 
        value == "Desconhecido" || 
        value == "Error") {
        return label_color + label + RESET + B_RED + value + RESET;
    }
    
    return label_color + label + RESET + value_color + value + RESET;
}

int main(int argc, char* argv[]) {
    using namespace Colors;

    Config config;
    config.load_config();

    std::string label_color_str = config.get_string("color_label", "b_white");
    std::string value_color_str = config.get_string("color_value", "white");

    std::string label_color = config.get_color_ansi(label_color_str);
    std::string value_color = config.get_color_ansi(value_color_str);

    std::string distro_atual = get_distro(); 
    int ascii_width = 0;
    
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg.length() > 1 && arg[0] == '-') {
            distro_atual = arg.substr(1); 
        }
    }

    std::vector<std::string> ascii_art = get_ascii_art(distro_atual, ascii_width);

    std::string user_host = get_user_host();
    
    std::string separator = "";
    for(int i=0; i<20; ++i) separator += "-";

    std::vector<std::string> info;
    
    if (config.is_enabled("show_os"))        info.push_back(format_info(get_distro_icon(distro_atual) + "OS: ", get_distro(), label_color, value_color));
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
    size_t total_linhas = std::max(ascii_art.size(), info_lines_count);

    std::cout << std::endl; 

    // Definimos a largura física para empurrar o texto.
    int margin_left = (ascii_art.size() > 20) ? 55 : 45;

    for (size_t i = 0; i < total_linhas; ++i) {
        std::cout << "  "; 

        bool has_logo_line = (i < ascii_art.size());
        
        
        if (has_logo_line) {
            std::cout << rtrim(ascii_art[i]);
        }

        
        std::cout << "\033[" << margin_left << "G";

        // 3. Imprime os dados do sistema na direita
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

    // Blocos de Cores
    std::cout << "  "; 
    for(int i = 40; i <= 47; ++i) std::cout << "\033[" << i << "m   \033[0m";
    std::cout << std::endl << "  "; 
    for(int i = 100; i <= 107; ++i) std::cout << "\033[" << i << "m   \033[0m";
    std::cout << std::endl << std::endl;

    return 0;
}
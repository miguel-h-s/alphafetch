#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include "fetch.hpp"
#include "logos.hpp"
#include "colors.hpp" 
#include "config.hpp"


std::string format_info(const std::string& label, const std::string& value) {
    using namespace Colors;
    
    
    if (value.find("BRUH") != std::string::npos || 
        value == "Desconhecido" || 
        value == "Error") {
        return B_WHITE + label + RESET + B_RED + value + RESET;
    }
    
  
    return B_WHITE + label + RESET + value;
}

int main() {
    using namespace Colors;

    
    Config config;
    config.load_config();

    
    std::string distro_atual = get_distro(); 
    int ascii_width = 0;
    
    
    std::vector<std::string> ascii_art = get_ascii_art(distro_atual, ascii_width);

    
    
    
    std::string user_host = get_user_host();
    
    
    std::string separator = "";
    for(int i=0; i<20; ++i) separator += "-";

    
    
    std::vector<std::string> info;
    
    if (config.is_enabled("show_os"))       info.push_back(format_info(i_os      + "OS:         ", get_distro()));
    if (config.is_enabled("show_kernel"))   info.push_back(format_info(i_kernel  + "Kernel:     ", get_kernel()));
    if (config.is_enabled("show_uptime"))   info.push_back(format_info(i_uptime  + "Uptime:     ", get_uptime()));
    if (config.is_enabled("show_shell"))    info.push_back(format_info(i_shell   + "Shell:      ", get_shell()));
    if (config.is_enabled("show_packages")) info.push_back(format_info(i_pkgs    + "Packages:   ", get_packages()));
    if (config.is_enabled("show_wm"))       info.push_back(format_info(i_wm      + "WM:         ", get_wm()));
    if (config.is_enabled("show_terminal")) info.push_back(format_info(i_term    + "Terminal:   ", get_terminal()));
    
    if (!info.empty()) info.push_back(""); 
    
    if (config.is_enabled("show_cpu"))      info.push_back(format_info(i_cpu     + "CPU:        ", get_cpu()));
    if (config.is_enabled("show_gpu"))      info.push_back(format_info(i_gpu     + "GPU:        ", get_gpu_name()));
    if (config.is_enabled("show_ram"))      info.push_back(format_info(i_ram     + "RAM:        ", get_ram()));
    if (config.is_enabled("show_disk"))     info.push_back(format_info(i_disk    + "Disk:       ", get_disk()));
    if (config.is_enabled("show_ip"))       info.push_back(format_info(i_ip      + "IP local:   ", get_local_ip()));
    if (config.is_enabled("show_music"))    info.push_back(format_info(i_music   + "Music:      ", get_music()));
    
    info.push_back(""); // Linha vazia separadora
    
    if (config.is_enabled("show_theme"))    info.push_back(format_info(i_theme   + "Theme:      ", get_gtk_theme()));
    if (config.is_enabled("show_icons"))    info.push_back(format_info(i_icons   + "Icons:      ", get_icon_theme()));
    if (config.is_enabled("show_cursor"))   info.push_back(format_info(i_cursor  + "Cursor:     ", get_cursor_theme()));
    if (config.is_enabled("show_font"))     info.push_back(format_info(i_font    + "Font:       ", get_font()));


    

    size_t info_lines_count = info.size() + 2; // Total de linhas de informação
    size_t max_linhas = std::max(ascii_art.size(), info_lines_count);

    
    size_t vertical_offset = 0;
    if (info_lines_count > ascii_art.size()) {
        vertical_offset = (info_lines_count - ascii_art.size()) / 2;
    }

    std::cout << std::endl; 

    for (size_t i = 0; i < max_linhas; ++i) {
        
        std::cout << "  "; 
        
        
        
        
        if (i >= vertical_offset && (i - vertical_offset) < ascii_art.size()) {
            std::cout << ascii_art[i - vertical_offset];
        } else {
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

    std::cout << std::endl << std::endl; 

    
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
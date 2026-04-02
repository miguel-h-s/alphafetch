#include "fetch.hpp"
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

// Re-usando a função exec_command aqui para simplicidade.
// O ideal seria criar um 'utils.cpp' com ela e incluir no Makefile.
extern std::string exec_command(const char* cmd); 

// Função auxiliar genérica para gsettings
std::string get_gsettings_value(const char* schema, const char* key) {
    try {
        std::string cmd = "gsettings get ";
        cmd += schema;
        cmd += " ";
        cmd += key;
        
        std::string raw_output = exec_command(cmd.c_str());
        
        // gsettings retorna com aspas simples: 'Adwaita-dark'
        // Precisamos remover as aspas
        if (raw_output.length() >= 3 && raw_output.front() == '\'' && raw_output.back() == '\n') {
            raw_output.pop_back(); // Remove \n
            return raw_output.substr(1, raw_output.length() - 2); // Remove as aspas
        }
        return "BRUH";
    } catch (...) {
        return "não é compativel com KDE no momento";
    }
}

std::string get_gtk_theme() {
    return get_gsettings_value("org.gnome.desktop.interface", "gtk-theme");
}

std::string get_icon_theme() {
    return get_gsettings_value("org.gnome.desktop.interface", "icon-theme");
}

std::string get_cursor_theme() {
    std::string theme = get_gsettings_value("org.gnome.desktop.interface", "cursor-theme");
    
    
    if (theme.empty() || theme == "Unknown" || theme == "Error") {
        char* xcursor = getenv("XCURSOR_THEME");
        if (xcursor != nullptr) {
            return std::string(xcursor);
        }
        return "\033[1;31mBRUH\033[0m"; 
    }
    
    return theme;
}

std::string get_font() {
    return get_gsettings_value("org.gnome.desktop.interface", "font-name");
}
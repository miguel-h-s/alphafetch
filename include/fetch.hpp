#pragma once
#include <string>

const std::string c_reset = "\033[0m";
const std::string c_bold  = "\033[1m";
const std::string c_cyan  = "\033[36m";
const std::string c_green = "\033[32m"; // Para o user@host

// Função utilitária para gerar a barra de progresso
inline std::string make_progress_bar(double current, double total) {
    int bar_width = 10; // Tamanho da barra (10 blocos)
    double percentage = current / total;
    int filled_width = percentage * bar_width;

    std::string bar = "[";
    for (int i = 0; i < bar_width; ++i) {
        if (i < filled_width) {
            bar += "█"; // Bloco cheio
        } else {
            bar += "░"; // Bloco vazio
        }
    }
    bar += "]";
    return bar;
}

// Funções para capturar os dados do sistema
std::string get_distro();
std::string get_kernel();
std::string get_shell();
std::string get_wm();
std::string get_terminal();
std::string get_cpu();
std::string get_gpu_name();
std::string get_uptime();
std::string get_user_host();
std::string get_gtk_theme();
std::string get_icon_theme();
std::string get_cursor_theme();
std::string get_font();
std::string get_ram();
std::string get_disk();
std::string get_packages();
std::string get_local_ip();
std::string get_battery();
std::string get_music();
#include <iostream>
#include <filesystem>
#include <string>
#include "fetch.hpp"

namespace fs = std::filesystem;

// Função auxiliar para contar arquivos em uma pasta baseado na extensão
int count_files_in_dir(const std::string& path, const std::string& extension) {
    int count = 0;
    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            for (const auto& entry : fs::directory_iterator(path)) {
                if (entry.path().extension() == extension) {
                    count++;
                }
            }
        }
    } catch (...) {
        return -1; // Retorna -1 se der erro de permissão
    }
    return count;
}

std::string get_packages() {
    std::string result = "";

    // debian/ubuntu
    int dpkg_count = count_files_in_dir("/var/lib/dpkg/info", ".list");
    if (dpkg_count > 0) {
        result += std::to_string(dpkg_count) + " (dpkg)";
    }

    // arch
    
    try {
        std::string pacman_path = "/var/lib/pacman/local";
        if (fs::exists(pacman_path) && fs::is_directory(pacman_path)) {
            int pacman_count = 0;
            for (const auto& entry : fs::directory_iterator(pacman_path)) {
                if (entry.is_directory()) pacman_count++;
            }
            if (pacman_count > 0) {
                if (!result.empty()) result += ", ";
                result += std::to_string(pacman_count) + " (pacman)";
            }
        }
    } catch (...) {}

    // fedora
    if (result.empty() && fs::exists("/usr/bin/rpm")) {
        FILE* pipe = popen("rpm -qa | wc -l", "r");
        if (pipe) {
            char buffer[128];
            if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
                std::string rpm_count = buffer;
                // Remove a quebra de linha
                if (!rpm_count.empty() && rpm_count.back() == '\n') rpm_count.pop_back();
                result = rpm_count + " (rpm)";
            }
            pclose(pipe);
        }
    }

    // flatpak
    int flatpak_count = count_files_in_dir("/var/lib/flatpak/app", "");
    if (flatpak_count > 0) {
        if (!result.empty()) result += ", ";
        result += std::to_string(flatpak_count) + " (flatpak)";
    }
    
    if (result.empty()) {
        return "Desconhecido";
    }

    return result;
}
#include "fetch.hpp"
#include <sys/statvfs.h>
#include <iostream>
#include <iomanip>
#include <sstream>

std::string get_disk() {
    struct statvfs vfs;
    // Pega as info da partição raiz "/"
    if (statvfs("/", &vfs) != 0) {
        return "Unknown";
    }

    // Tamanho total em Bytes
    double total_bytes = (double)vfs.f_blocks * vfs.f_frsize;
    // Tamanho disponível para usuários normais em Bytes
    double available_bytes = (double)vfs.f_bavail * vfs.f_frsize;
    double used_bytes = total_bytes - available_bytes;

    // Convertendo para Gigabytes (GB)
    double total_gb = total_bytes / (1024.0 * 1024.0 * 1024.0);
    double used_gb = used_bytes / (1024.0 * 1024.0 * 1024.0);

    // Calculando a porcentagem de uso
    int percent_used = 0;
    if (total_bytes > 0) {
        percent_used = (used_bytes / total_bytes) * 100;
    }

    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << used_gb << " GB / " << total_gb << " GB (" << percent_used << "%)";
    
    return ss.str();
}
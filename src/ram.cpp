#include "fetch.hpp"
#include <sys/sysinfo.h>
#include <iostream>
#include <iomanip>
#include <sstream>

std::string get_ram() {
    struct sysinfo si;
    if (sysinfo(&si) != 0) {
        return "BRUH";
    }

    // Convertendo bytes para Gigabytes (GiB)
    double total_ram = si.totalram * si.mem_unit / (1024.0 * 1024.0 * 1024.0);
    
    // Memória livre + buffers + cache (simplificado para "memória disponível")
    double free_ram = (si.freeram + si.bufferram) * si.mem_unit / (1024.0 * 1024.0 * 1024.0);
    
    // Memória realmente usada
    double used_ram = total_ram - free_ram;

    // Formatando para aparecer com apenas 1 casa decimal (ex: 1.5 GiB)
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << used_ram << " GiB / " << total_ram << " GiB";
    
    return ss.str();
}
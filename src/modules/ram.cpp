#include "fetch.hpp"
#include <sys/sysinfo.h>
#include <iostream>
#include <iomanip>
#include <sstream>

std::string get_ram() {
    struct sysinfo si;
    if (sysinfo(&si) != 0) {
        return "unknown-ram";
    }

    double total_ram = si.totalram * si.mem_unit / (1024.0 * 1024.0 * 1024.0);
    double free_ram = (si.freeram + si.bufferram) * si.mem_unit / (1024.0 * 1024.0 * 1024.0);
    double used_ram = total_ram - free_ram;

    
    std::string bar = make_progress_bar(used_ram, total_ram);

    std::stringstream ss;
    ss << bar << " " << std::fixed << std::setprecision(1) << used_ram << " GiB / " << total_ram << " GiB";
    
    return ss.str();
}
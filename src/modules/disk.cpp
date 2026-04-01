#include "fetch.hpp"
#include <sys/statvfs.h>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "fetch.hpp"
#include <sys/statvfs.h>
#include <iostream>
#include <iomanip>
#include <sstream>

std::string get_disk() {
    struct statvfs vfs;
    if (statvfs("/", &vfs) != 0) {
        return "\033[1;31mBRUH\033[0m";
    }

    double total_bytes = (double)vfs.f_blocks * vfs.f_frsize;
    double available_bytes = (double)vfs.f_bavail * vfs.f_frsize;
    double used_bytes = total_bytes - available_bytes;

    double total_gb = total_bytes / (1024.0 * 1024.0 * 1024.0);
    double used_gb = used_bytes / (1024.0 * 1024.0 * 1024.0);

    int percent_used = 0;
    if (total_bytes > 0) {
        percent_used = (used_bytes / total_bytes) * 100;
    }

    // Chamando a barra de progresso do fetch.hpp
    std::string bar = make_progress_bar(used_bytes, total_bytes);

    std::stringstream ss;
    ss << bar << " " << std::fixed << std::setprecision(1) << used_gb << " GB / " << total_gb << " GB (" << percent_used << "%)";
    
    return ss.str();
}
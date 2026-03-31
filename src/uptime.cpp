#include <sys/sysinfo.h>
#include <string>

std::string get_uptime() {
    struct sysinfo info;
    sysinfo(&info);
    
    long horas = info.uptime / 3600;
    long minutos = (info.uptime % 3600) / 60;
    
    return std::to_string(horas) + "h " + std::to_string(minutos) + "m";
}
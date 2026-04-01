#include <string>
#include <fstream>

std::string get_kernel() {
    std::ifstream file("/proc/sys/kernel/osrelease");
    std::string line;
    std::getline(file, line);
    return line;
}
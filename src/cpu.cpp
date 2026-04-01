#include <fstream>
#include <string>

std::string get_cpu() {
    std::ifstream file("/proc/cpuinfo");
    std::string line;
    while (std::getline(file, line)) {
        // Procura a linha do modelo
        if (line.rfind("model name", 0) == 0) {
            size_t pos = line.find(": ");
            if (pos != std::string::npos) {
                return line.substr(pos + 2); // Pula o ": " e pega o nome
            }
        }
    }
    return "\033[1;31mBRUH\033[0m";
}
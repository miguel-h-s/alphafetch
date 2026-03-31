#include <fstream>
#include <string>

std::string get_distro() {
    std::ifstream file("/etc/os-release");
    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind("PRETTY_NAME=", 0) == 0) {
            // Pega o texto ignorando o 'PRETTY_NAME="' (13 caracteres)
            std::string name = line.substr(13);
            // Remove a última aspa
            name.pop_back();
            return name;
        }
    }
    return "DISTRO = BRUH";
}
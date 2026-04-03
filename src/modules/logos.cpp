#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 

std::vector<std::string> get_ascii_art(const std::string& distro, int& width) {
    std::vector<std::string> lines;
    
    
    const char* home_dir = std::getenv("HOME");
    std::string path;
    
    if (home_dir != nullptr) {
        path = std::string(home_dir) + "/.config/alphafetch/logos/" + distro + ".txt";
    } else {
        path = "logos/" + distro + ".txt";
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        
        std::string fallback_path = std::string(home_dir) + "/.config/alphafetch/logos/default.txt";
        file.open(fallback_path);
        
        if (!file.is_open()) {
            lines.push_back("Logo não encontrada!");
            lines.push_back("Crie a pasta ~/.config/alphafetch/logos/");
            return lines;
        }
    }

    std::string line;
    width = 0;
    while (std::getline(file, line)) {
        lines.push_back(line);
        if ((int)line.length() > width) {
            width = line.length();
        }
    }
    
    return lines;
}
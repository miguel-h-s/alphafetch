#include "logos.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

std::vector<std::string> get_ascii_art(const std::string& distro, int& width) {
    std::vector<std::string> logo;
    
    // Forçamos a largura exata da logo do Debian que está no seu print!
    width = 24;

    std::string distro_lower = distro;
    std::transform(distro_lower.begin(), distro_lower.end(), distro_lower.begin(), ::tolower);

    if (distro_lower.find("debian") != std::string::npos) distro_lower = "debian";
    else if (distro_lower.find("arch") != std::string::npos) distro_lower = "arch";
    else if (distro_lower.find("gentoo") != std::string::npos) distro_lower = "gentoo";

    std::string path = "logos/" + distro_lower + ".txt";
    std::ifstream file(path);

    if (!file.is_open()) {
        width = 3;
        return {"[?]", "[?]", "[?]"};
    }

    std::string line;
    while (std::getline(file, line)) {
        logo.push_back(line);
    }

    file.close();
    return logo;
}
#pragma once

#include <vector>
#include <string>

// Retorna a arte ASCII baseada no nome da distro
std::vector<std::string> get_ascii_art(const std::string& distro_name, int& width);


#include "fetch.hpp"
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <regex>


std::string exec_command(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, void(*)(FILE*)> pipe(popen(cmd, "r"), [](FILE* f) { if (f) pclose(f); });
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string get_gpu_name() {
    try {
        
        std::string raw_output = exec_command("lspci | grep -i vga");
        
        
        
        
        std::regex gpu_regex("controller: ([^(]+)");
        std::smatch match;

        if (std::regex_search(raw_output, match, gpu_regex) && match.size() > 1) {
            std::string gpu_name = match[1].str();
            
            
            gpu_name.erase(gpu_name.find_last_not_of(" \n\r\t") + 1);
            
            return gpu_name;
        } else {
            return "unknown-gpu";
        }
    } catch (...) {
        return "\033[1;31mERROR\033[0m";
    }
}
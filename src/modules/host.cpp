#include "fetch.hpp"
#include <unistd.h>
#include <fstream>
#include <iostream>

std::string get_user_host() {
    char hostname[1024];
    hostname[1023] = '\0';
    
    if (gethostname(hostname, 1023) != 0) {
        return "\033[1;31mBRUH@BRUH\033[0m";
    }

    
    char* user = getenv("USER");
    std::string user_str = (user != nullptr) ? user : "unknown";

    
    return c_green + c_bold + user_str + c_reset + "@" + c_green + c_bold + std::string(hostname) + c_reset;
}
#include <iostream>
#include <string>
#include "fetch.hpp"

std::string get_local_ip() {
    FILE* pipe = popen("hostname -I | awk '{print $1}'", "r");
    if (!pipe) return "unknown-iplocal";

    char buffer[128];
    std::string result = "";
    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result = buffer;
    }
    pclose(pipe);

    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    return result.empty() ? " offline" : result;
}
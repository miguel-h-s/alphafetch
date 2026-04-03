#pragma once
#include <string>

namespace Colors {
    // Cores padrão (Texto normal)
    const std::string RESET   = "\033[0m";
    const std::string RED     = "\033[31m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string BLUE    = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN    = "\033[36m";
    const std::string WHITE   = "\033[37m";
    const std::string BOLD    = "\033[1m";

    // Cores Negrito (Bright/Bold)
    const std::string B_RED     = "\033[1;31m";
    const std::string B_GREEN   = "\033[1;32m";
    const std::string B_YELLOW  = "\033[1;33m";
    const std::string B_BLUE    = "\033[1;34m";
    const std::string B_MAGENTA = "\033[1;35m";
    const std::string B_CYAN    = "\033[1;36m";
    const std::string B_WHITE   = "\033[1;37m";
}
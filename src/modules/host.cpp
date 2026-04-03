#include "fetch.hpp"
#include "colors.hpp"

#include <unistd.h>
#include <cstdlib>
#include <string>

// sistema

namespace System {

    std::string get_hostname() {
        char buffer[256]; 

        if (gethostname(buffer, sizeof(buffer)) != 0) {
            return "unknown-host";
        }

        buffer[sizeof(buffer) - 1] = '\0'; 

        return std::string(buffer);
    }

    std::string get_user() {
        const char* user = std::getenv("USER");
        return user ? std::string(user) : "unknown-user";
    }
}

// formata

static std::string format_user_host(const std::string& user,
                                    const std::string& host) {
    return Colors::GREEN + Colors::BOLD + user + Colors::RESET +
           "@" +
           Colors::GREEN + Colors::BOLD + host + Colors::RESET;
}


std::string get_user_host() {
    return format_user_host(
        System::get_user(),
        System::get_hostname()
    );
}
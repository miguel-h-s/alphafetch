#include <string>
#include <vector>
#include <algorithm>

std::string to_lower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

std::string get_distro_icon(const std::string& distro_name) {
    static const std::vector<std::pair<std::string, std::string>> distros = {
        {"debian", ""},
        {"arch", ""},
        {"ubuntu", ""},
        {"mint", ""},
        {"fedora", ""},
        {"gentoo", ""},
        {"slackware", ""},
        {"void", ""},
        {"manjaro", ""},
        {"pop", ""},
        {"opensuse", ""},
        {"nixos", ""}
    };

    std::string name = to_lower(distro_name);

    for (const auto& [key, icon] : distros) {
        if (name.find(key) != std::string::npos) {
            return icon;
        }
    }

    return "";
}
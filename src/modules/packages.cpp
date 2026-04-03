#include <filesystem>
#include <string>
#include <vector>
#include <optional>
#include <cstdio>

#include "fetch.hpp"

namespace fs = std::filesystem;

// utils

int count_files(const std::string& path, const std::string& ext = "") {
    try {
        if (!fs::exists(path) || !fs::is_directory(path))
            return 0;

        int count = 0;

        for (const auto& entry : fs::directory_iterator(path)) {
            if (ext.empty() || entry.path().extension() == ext) {
                count++;
            }
        }

        return count;
    } catch (const std::exception&) {
        return 0; 
    }
}

std::optional<int> count_dirs(const std::string& path) {
    try {
        if (!fs::exists(path) || !fs::is_directory(path))
            return std::nullopt;

        int count = 0;

        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_directory())
                count++;
        }

        return count > 0 ? std::optional(count) : std::nullopt;

    } catch (const std::exception&) {
        return std::nullopt;
    }
}

std::optional<int> count_rpm() {
    FILE* pipe = popen("rpm -qa | wc -l", "r");
    if (!pipe) return std::nullopt;

    char buffer[128];
    std::string result;

    if (fgets(buffer, sizeof(buffer), pipe)) {
        result = buffer;
    }

    pclose(pipe);

    if (!result.empty() && result.back() == '\n')
        result.pop_back();

    try {
        return std::stoi(result);
    } catch (...) {
        return std::nullopt;
    }
}



std::string get_packages() {
    std::vector<std::string> parts;

    // dpkg
    int dpkg = count_files("/var/lib/dpkg/info", ".list");
    if (dpkg > 0) {
        parts.push_back(std::to_string(dpkg) + " (dpkg)");
    }

    // pacman
    if (auto pacman = count_dirs("/var/lib/pacman/local")) {
        parts.push_back(std::to_string(*pacman) + " (pacman)");
    }

    // rpm
    if (parts.empty()) {
        if (auto rpm = count_rpm()) {
            parts.push_back(std::to_string(*rpm) + " (rpm)");
        }
    }

    // flatpak
    int flatpak = count_files("/var/lib/flatpak/app");
    if (flatpak > 0) {
        parts.push_back(std::to_string(flatpak) + " (flatpak)");
    }

    if (parts.empty()) {
        return "unknown-packages";
    }

    // join
    std::string result;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i > 0) result += ", ";
        result += parts[i];
    }

    return result;
}
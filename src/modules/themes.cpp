#include "fetch.hpp"
#include <cstdlib>
#include <string>


extern std::string exec_command(const char* cmd);



std::string clean_gsettings_output(std::string out) {
    // remove '\n'
    if (!out.empty() && out.back() == '\n')
        out.pop_back();

    
    if (out.size() >= 2 && out.front() == '\'' && out.back() == '\'') {
        out = out.substr(1, out.size() - 2);
    }

    return out;
}

std::string get_gsettings_value(const char* schema, const char* key) {
    std::string cmd = "gsettings get ";
    cmd += schema;
    cmd += " ";
    cmd += key;

    std::string output = exec_command(cmd.c_str());
    output = clean_gsettings_output(output);

    if (output.empty() || output == "null") {
        return "";
    }

    return output;
}

// gtk

std::string get_gtk_theme() {
    std::string val = get_gsettings_value("org.gnome.desktop.interface", "gtk-theme");
    return val.empty() ? "unknown-theme" : val;
}

std::string get_icon_theme() {
    std::string val = get_gsettings_value("org.gnome.desktop.interface", "icon-theme");
    return val.empty() ? "unknown-icons" : val;
}

std::string get_cursor_theme() {
    std::string val = get_gsettings_value("org.gnome.desktop.interface", "cursor-theme");

    if (!val.empty()) {
        return val;
    }

    // fallback universal
    const char* xcursor = std::getenv("XCURSOR_THEME");
    return xcursor ? std::string(xcursor) : "unknown-cursor";
}

std::string get_font() {
    std::string val = get_gsettings_value("org.gnome.desktop.interface", "font-name");
    return val.empty() ? "unknown-font" : val;
}
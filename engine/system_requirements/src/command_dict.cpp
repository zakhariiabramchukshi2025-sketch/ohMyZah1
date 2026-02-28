#include "../includes/command_dict.hpp"

namespace cmd_dict {

    const std::unordered_map<std::string, std::vector<std::string>> tree = {
        {"", {"iot", "sys", "pyvo", "cd", "clear", "pwd", "exit"}}, // lvl 1
        
        
        // lvl 2
        // IOT
        {"iot", {"camera", "tv", "lock", "phone", "info", "turn_on_all"}},
        
        // SYSTEM
        {"sys", {"reboot", "status", "update", "logs"}},
        
        // PYVO
        {"pyvo", {"info", "--version", "--update"}},

        
        
        // lvl 3
        // iot camera
        {"iot camera", {"turn_on", "turn_off", "stream", "night_vision", "setup"}},
        
        // iot lock
        {"iot lock", {"unlock", "lock", "status", "setup"}},
        
        // iot tv
        {"iot tv", {"turn_on", "turn_off", "diagnostic", "setup"}},

        // system logs
        {"sys logs", {"show", "clear", "export"}}
    };

}

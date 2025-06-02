// ConfigManager.h
#pragma once
#include <string>
#include <nlohmann/json.hpp>

class ConfigManager {
public:
    static nlohmann::json configData;
    static void SaveConfig(const std::string& path);
    static void LoadConfig(const std::string& path);
};

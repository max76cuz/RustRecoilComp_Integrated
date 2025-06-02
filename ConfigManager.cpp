// ConfigManager.cpp
#include "ConfigManager.h"
#include <fstream>

nlohmann::json ConfigManager::configData;

void ConfigManager::SaveConfig(const std::string& path) {
    std::ofstream file(path);
    file << configData.dump(4);
    file.close();
}

void ConfigManager::LoadConfig(const std::string& path) {
    std::ifstream file(path);
    if (file.is_open()) {
        file >> configData;
        file.close();
    }
}

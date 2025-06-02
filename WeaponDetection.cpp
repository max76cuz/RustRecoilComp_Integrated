// WeaponDetection.cpp
#include "WeaponDetection.h"
#include "ConfigManager.h"

std::string WeaponDetection::GetWeaponName(int weaponId) {
    for (const auto& weapon : ConfigManager::configData["weapons"]) {
        if (weapon["id"] == weaponId) {
            return weapon["name"];
        }
    }
    return "Unknown";
}

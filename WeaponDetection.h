#pragma once
#include <unordered_map>
#include <string>

class WeaponDetection {
public:
    static std::string GetWeaponName(int weaponId);
};

// WeaponDetection.cpp
#include "WeaponDetection.h"

std::unordered_map<int, std::string> weaponIdToName = {
    {1545779598, "Assault Rifle (AK-47)"},
    {1588298435, "Bolt Action Rifle"},
    {1796682209, "Custom SMG"},
    {1318558775, "MP5A4"},
    // Add more weapons...
};

std::string WeaponDetection::GetWeaponName(int weaponId) {
    if (weaponIdToName.count(weaponId))
        return weaponIdToName[weaponId];
    return "Unknown";
}

#pragma once
#include <string>

class RecoilManager {
public:
    static void ApplyRecoil(const std::string& weaponName);
};

// RecoilManager.cpp
#include "RecoilManager.h"
#include "ConfigManager.h"
#include "DriverComm.h"

void RecoilManager::ApplyRecoil(const std::string& weaponName) {
    auto pattern = ConfigManager::configData[weaponName];
    int x = pattern["x"].get<int>();
    int y = pattern["y"].get<int>();
    DriverComm::SendMouseMove(x, y);
}

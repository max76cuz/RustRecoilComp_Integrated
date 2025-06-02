// RecoilManager.cpp
#include "RecoilManager.h"
#include "ConfigManager.h"
#include "DriverComm.h"
#include <thread>

void RecoilManager::ApplyRecoil(const std::string& weaponName) {
    // Find the weapon’s pattern
    for (const auto& weapon : ConfigManager::configData["weapons"]) {
        if (weapon["name"] == weaponName) {
            const auto& pattern = weapon["recoil_pattern"];
            for (const auto& step : pattern) {
                int x = step["x"];
                int y = step["y"];

                // Human-like smoothing & randomization
                int dx = x + (rand() % 2 - 1); // random -1/0/1
                int dy = y + (rand() % 2 - 1);

                DriverComm::SendMouseMove(dx, dy);

                // Add delay between shots to simulate real firing rate
                std::this_thread::sleep_for(std::chrono::milliseconds(30));
            }
            break;
        }
    }
}
